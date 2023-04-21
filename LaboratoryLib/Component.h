/**
 * @file Component.h
 * @author Ravi Grewal
 *
 * A component in the laboratory
 */

#ifndef CANADIANEXPERIENCE_COMPONENT_H
#define CANADIANEXPERIENCE_COMPONENT_H

#include <wx/xml/xml.h>
#include "Polygon.h"

class WorkingLaboratory;

/**
 * A component in the laboratory
 */
class Component {
private:

    /// The working lab this component belongs to
    WorkingLaboratory* mLaboratory = nullptr;

    /// The name of this component
    std::wstring mName;

    /// The voltage of this component
    double mVoltage = 0;

    /// The current of this component
    double mCurrent = 0;

    /// The time for this component
    double mTime = 0;

    /// The position of this component
    wxPoint mPosition = {0, 0};

    /// The images directory for this component
    std::wstring mImagesDir;

public:

    /**
     * Construct a component
     * @param imagesDir Images directory
     */
    Component(std::wstring imagesDir) : mImagesDir(imagesDir) {}

    /// Destructor
    virtual ~Component() = default;

    /// Copy constructor/disabled
    Component(const Component&) = delete;

    /// Assignment operator/disabled
    void operator=(const Component&) = delete;

    /**
     * Draw the component at the currently specified location
     * @param graphics Graphics object to render to
     * @param x X location
     * @param y Y location
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) {}

    /**
     * Facilitate movement of power through components
     * @param voltage Voltage to pass
     * @return current consumed as double
     */
    virtual double Power(double voltage) { return 0; }

    /**
     * Facilitate physical movement of components
     * @param duration Duration of movement
     */
    virtual void Move(double duration) {}

    /**
     * Set the working laboratory for this component
     * @param laboratory
     */
    void SetLaboratory(WorkingLaboratory* laboratory) { mLaboratory = laboratory; }

    /**
     * Get the working laboratory for this component
     * @return WorkingLaboratory
     */
    WorkingLaboratory* GetLaboratory() { return mLaboratory; }

    /**
     * Get the position
     * @return position as wxPoint
     */
    wxPoint GetPosition() { return mPosition; }

    /**
     * Set the position
     * @param x x position
     * @param y y position
     */
    virtual void SetPosition(int x, int y) { mPosition = wxPoint(x, y); }

    /**
     * Get the images directory
     * @return images directory as wstring
     */
    std::wstring GetImagesDir() { return mImagesDir; }

    /**
     * Get the voltage
     * @return voltage
     */
    double GetVoltage() { return mVoltage; }

    /**
     * Set the voltage
     * @param voltage to set
     */
    void SetVoltage(double voltage) { mVoltage = voltage; }

    /**
     * Get the current
     * @return current
     */
    double GetCurrent() { return mCurrent; }

    /**
     * Set the current
     * @param current to set
     */
    void SetCurrent(double current) { mCurrent = current; }

    /**
     * Update the component
     * @param time Time used in the update
     */
    virtual void Update(double time) { mTime = time; }

    /**
     * Set the name for this component
     * @param name Name for this component
     */
    void SetName(std::wstring name) { mName = name; }

    /**
     * Get the name of this component
     * @return name as a wstring
     */
    std::wstring GetName() { return mName; }

    /**
     * Handle an animation XML event
     * @param node Node with animation details
     */
    virtual void XmlEvent(wxXmlNode* node) {}

    /**
     * Get the time
     * @return time
     */
    double GetTime() { return mTime; }
    

};

#endif //CANADIANEXPERIENCE_COMPONENT_H
