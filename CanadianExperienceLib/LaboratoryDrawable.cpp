/**
 * @file LaboratoryDrawable.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "LaboratoryDrawable.h"
#include "Actor.h"
#include "Picture.h"
#include "Timeline.h"

using namespace std;

/**
 * Construct a laboratory drawable
 * @param name Name of this drawable
 * @param resourcesDir Resources Directory
 */
LaboratoryDrawable::LaboratoryDrawable(const std::wstring &name, std::wstring resourcesDir) : Drawable(name)
{
    LaboratoryFactory factory(resourcesDir);
    mLaboratory = factory.CreateLaboratory();
}

/**
 * Draw a laboratory drawable item
 * @param graphics Graphics context to render to
 */
void LaboratoryDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    //
    // Get the timeline's current frame and send it to the laboratory frame
    //
    mLaboratory->SetLocation(mPlacedPosition);
    mLaboratory->SetLaboratoryFrame(GetActor()->GetPicture()->GetTimeline()->GetCurrentFrame());
    mLaboratory->DrawLaboratory(graphics);
}

/**
 * Select the laboratory to display
 * @param parent Parent frame for dialog box rendering
 */
void LaboratoryDrawable::SelectLab(wxFrame *parent)
{
    LaboratoryDialog dlg(parent, mLaboratory);
    if (dlg.ShowModal() == wxID_OK)
    {
        // A laboratory has been selected
    }
    GetActor()->GetPicture()->UpdateObservers();  // force a redraw
}