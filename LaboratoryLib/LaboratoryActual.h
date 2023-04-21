/**
 * @file LaboratoryActual.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_LABORATORYACTUAL_H
#define CANADIANEXPERIENCE_LABORATORYACTUAL_H

#include "Laboratory.h"
#include "WorkingLaboratory.h"

/**
 * Derived laboratory to support components
 */
class LaboratoryActual : public Laboratory {
private:

    /// The location of the laboratory
    wxPoint mLocation = {0, 0};

    /// The current frame
    int mFrame = 0;

    /// The frame rate
    double mFrameRate = 30;

    /// The laboratory number
    int mLaboratoryNumber = 1;

    /// The working laboratory
    std::shared_ptr<WorkingLaboratory> mWorkingLaboratory = nullptr;

    /// The resources directory
    std::wstring mResourcesDirectory;

public:

    /// Constructor
    LaboratoryActual(std::wstring resourcesDir);

    /// Destructor
    virtual ~LaboratoryActual() = default;

    /// Copy constructor/disabled
    LaboratoryActual(const LaboratoryActual&) = delete;

    /// Assignment operator/disabled
    void operator=(const LaboratoryActual&) = delete;

    /**
     * Set the frame rate
     * @param frameRate
     */
    void SetFrameRate(double frameRate) override { mFrameRate = frameRate; }

    /**
     * Get the current laboratory time
     * @return Laboratory time in seconds
     */
    double GetLaboratoryTime() override { return mFrame / (double)mFrameRate; }

    /**
     * Get the laboratory number
     * @return
     */
    int GetLaboratoryNumber() override { return mLaboratoryNumber; }

    /**
    * Set the laboratory number
    * @param laboratory An integer number. Each number makes a different laboratory
    */
    void SetLaboratoryNumber(int laboratory) override;

    /**
     * Get the location
     * @return
     */
    wxPoint GetLocation() override { return mLocation; }

    /**
     * Set the location
     * @param location
     */
    void SetLocation(wxPoint location) override { mLocation = location; }

    /**
    * Draw the laboratory at the currently specified location
    * @param graphics Graphics object to render to
    */
    void DrawLaboratory(std::shared_ptr<wxGraphicsContext> graphics) override { mWorkingLaboratory->DrawLaboratory(graphics, mLocation.x, mLocation.y); }

    void SetLaboratoryFrame(int frame);

    /**
     * Get the resources directory
     * @return resources directory
     */
    std::wstring GetResourcesDirectory() { return mResourcesDirectory; }

    void Reset();

};

#endif //CANADIANEXPERIENCE_LABORATORYACTUAL_H
