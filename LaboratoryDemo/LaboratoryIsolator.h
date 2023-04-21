/**
 * @file LaboratoryIsolator.h
 * @author Ravi Grewal
 *
 * This class makes it possible for LaboratoryDemoLib to be isolated from
 * LaboratoryLib completely, abstracting all laboratory functionality
 * to this single class, allowing for dependency injection into
 * LaboratoryDemoLib
 *
 * Do not modify this file!
 *
 * Do not try to include this file. It is for LaboratoryDemo use only.
 */

#ifndef LABORATORYDEMO_LABORATORYISOLATOR_H
#define LABORATORYDEMO_LABORATORYISOLATOR_H

#include <memory>
#include <ILaboratoryIsolator.h>
#include <laboratory-api.h>


/**
 * This class makes it possible for LaboratoryDemo to be isolated from
 * LaboratoryLib completely, abstracting all laboratory functionality
 * to this single class.
 */
class LaboratoryIsolator final : public ILaboratoryIsolator {
private:
    /// The laboratory we are isolating
    std::shared_ptr<Laboratory> mLaboratory;

public:
    /**
     * Constructor
     * @param resourcesDir Directory containing the program resources
     */
    explicit LaboratoryIsolator(std::wstring resourcesDir)
    {
        //
        // Use the LaboratoryFactory factory to create the laboratory object
        //
        LaboratoryFactory factory(resourcesDir);
        mLaboratory = factory.CreateLaboratory();
    }

    /**
     * Set the laboratory number
     * @param laboratory New laboratory number
     */
    void SetLaboratoryNumber(int laboratory) override
    {
        mLaboratory->SetLaboratoryNumber(laboratory);
    }

    /**
     * Get the current laboratory number
     * @return Laboratory number
     */
    int GetLaboratoryNumber() override
    {
        return mLaboratory->GetLaboratoryNumber();
    }

    /**
     * Set the laboratory location
     * @param location Location of the laboratory
     */
    void SetLocation(wxPoint location) override
    {
        mLaboratory->SetLocation(location);
    }

    /**
    * Set the current laboratory animation frame
    * @param frame Frame number
    */
    void SetLaboratoryFrame(int frame) override
    {
        mLaboratory->SetLaboratoryFrame(frame);
    }

    /**
     * Set the frame rate
     * @param rate Frame rate in frames per second
     */
    void SetFrameRate(double rate) override
    {
        mLaboratory->SetFrameRate(rate);
    }


    /**
     * Display the laboratory selection dialog box
     * @param parent Parent window for the dialog box
     * @return True if OK pressed
     */
    bool DoDialog(wxWindow* parent) override
    {
        LaboratoryDialog dialog(parent, mLaboratory);
        return (dialog.ShowModal() == wxID_OK);
    }

    /**
    * Draw the laboratory at the currently specified location
    * @param graphics Graphics object to render to
    */
    void DrawLaboratory(std::shared_ptr<wxGraphicsContext> graphics) override
    {
        mLaboratory->DrawLaboratory(graphics);
    }

    /**
     * Get the current laboratory time.
     * @return Laboratory time in seconds
     */
    double GetLaboratoryTime() override
    {
        return mLaboratory->GetLaboratoryTime();
    }

};

#endif //LABORATORYDEMO_LABORATORYISOLATOR_H
