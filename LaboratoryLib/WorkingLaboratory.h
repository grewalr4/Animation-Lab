/**
 * @file WorkingLaboratory.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_WORKINGLABORATORY_H
#define CANADIANEXPERIENCE_WORKINGLABORATORY_H

class Component;
class LaboratoryActual;
class ZPM;
class Event;

#include <wx/xml/xml.h>

/**
 * Working laboratory that holds components
 */
class WorkingLaboratory {
private:
    
    /// The laboratory number
    int mLaboratoryNumber = 1;

    /// The components in this laboratory
    std::vector<std::shared_ptr<Component>> mComponents;

    /// The ZPM for this laboratory
    std::shared_ptr<ZPM> mZPM = nullptr;

    /// The actual laboratory that this working lab is part of
    LaboratoryActual* mLaboratoryActual = nullptr;

    /// The animation events in this laboratory
    std::vector<std::shared_ptr<Event>> mEvents;

    /// The XML document for animation
    wxXmlDocument mXmlDoc;

public:

    WorkingLaboratory(int laboratoryNumber);

    /// Destructor
    virtual ~WorkingLaboratory() = default;

    /// Copy constructor/disabled
    WorkingLaboratory(const WorkingLaboratory&) = delete;

    /// Assignment operator/disabled
    void operator=(const WorkingLaboratory&) = delete;

    void AddComponent(std::shared_ptr<Component> component);

    void AddZPM(std::shared_ptr<ZPM> zpm);

    /**
     * Get the laboratory number
     * @return laboratory number
     */
    int GetLaboratoryNumber() { return mLaboratoryNumber; }

    /**
     * Get a laboratory component as position pos
     * @param pos
     * @return laboratory component
     */
    std::shared_ptr<Component> GetComponent(int pos) { return mComponents[pos]; }

    void DrawLaboratory(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);

    /**
     * Set the laboratory actual
     * @param laboratoryActual
     */
    void SetLaboratoryActual(LaboratoryActual* laboratoryActual) { mLaboratoryActual = laboratoryActual; }

    /**
     * Get the laboratory actual
     * @return
     */
    LaboratoryActual* GetLaboratoryActual() { return mLaboratoryActual; }

    wxPoint GetLocation();

    void Update(double time);

    void LoadScript(std::wstring path);

    void Animate(double time);

};

#endif //CANADIANEXPERIENCE_WORKINGLABORATORY_H
