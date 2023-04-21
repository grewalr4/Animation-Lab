/**
 * @file LaboratoryDrawable.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_LABORATORYDRAWABLE_H
#define CANADIANEXPERIENCE_LABORATORYDRAWABLE_H

#include "Drawable.h"
#include <laboratory-api.h>

/**
 * Adapter class to include the laboratory
 */
class LaboratoryDrawable : public Drawable {
private:

    /// The laboratory
    std::shared_ptr<Laboratory> mLaboratory = nullptr;

public:

    LaboratoryDrawable(const std::wstring &name, std::wstring resourcesDir);

    virtual ~LaboratoryDrawable() {}

    /** Default constructor disabled */
    LaboratoryDrawable() = delete;

    /** Copy constructor disabled */
    LaboratoryDrawable(const LaboratoryDrawable &) = delete;

    /** Assignment operator disabled */
    void operator=(const LaboratoryDrawable &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Test to see if we have been clicked on by the mouse
     * @param pos Position to test
     * @return true if clicked on
     */
    virtual bool HitTest(wxPoint pos) { return false; }

    void SelectLab(wxFrame* parent);

    /**
     * Set the lab number
     * @param labNum Lab num to set
     */
    void SetLabNum(int labNum) { mLaboratory->SetLaboratoryNumber(labNum); }

    /**
     * Get the lab number
     * @return lab number
     */
    int GetLabNum() { return mLaboratory->GetLaboratoryNumber(); }
};

#endif //CANADIANEXPERIENCE_LABORATORYDRAWABLE_H
