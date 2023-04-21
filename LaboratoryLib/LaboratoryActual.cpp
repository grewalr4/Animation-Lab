/**
 * @file LaboratoryActual.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include <wx/stdpaths.h>
#include "LaboratoryActual.h"
#include "Laboratory1Factory.h"
#include "Laboratory2Factory.h"

/// Directory containing images within the resources
const std::wstring ImagesDirectory = L"/images";

/// Default laboratory number
const int DefaultLaboratoryNumber = 1;

using namespace std;

/**
 * Construct a LaboratoryActual object
 * @param resourcesDir Resources directory
 */
LaboratoryActual::LaboratoryActual(std::wstring resourcesDir) : mResourcesDirectory(resourcesDir)
{
    SetLaboratoryNumber(DefaultLaboratoryNumber);
}

void LaboratoryActual::SetLaboratoryNumber(int laboratory)
{
    mLaboratoryNumber = laboratory;
    switch (mLaboratoryNumber)
    {
    case 1:
    {
        auto lab1Factory = Laboratory1Factory(mResourcesDirectory, mResourcesDirectory + ImagesDirectory);
        mWorkingLaboratory = lab1Factory.Create();
        break;
    }
    case 2:
    {
        auto lab2Factory = Laboratory2Factory(mResourcesDirectory, mResourcesDirectory + ImagesDirectory);
        mWorkingLaboratory = lab2Factory.Create();
        break;
    }
    default:
        break;
    }

    if (mWorkingLaboratory != nullptr)
    {
        mWorkingLaboratory->SetLaboratoryActual(this);
        mWorkingLaboratory->Update(0);  // force an initial update
    }
}

/**
 * Set the laboratory frame and update all components
 * @param frame
 */
void LaboratoryActual::SetLaboratoryFrame(int frame)
{
    if (frame < mFrame)
    {
        // We are going backwards in time,
        // reset to the beginning
        mFrame = -1;
        Reset();
    }

    while (mFrame < frame)
    {
        mFrame++;
        mWorkingLaboratory->Update(GetLaboratoryTime());
    }
}

/**
 * Reset the laboratory
 */
void LaboratoryActual::Reset()
{
    SetLaboratoryNumber(mLaboratoryNumber);  // force a reset on the laboratory
}
