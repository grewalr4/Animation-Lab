/**
 * @file PictureFactory.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "FrankFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "laboratory-api.h"
#include "LaboratoryDrawable.h"

using namespace std;

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the images for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    shared_ptr<Picture> picture = make_shared<Picture>();

    // Create and add the laboratory
    auto lab = make_shared<Actor>(L"LaboratoryActor");
    auto labDrawable = make_shared<LaboratoryDrawable>(L"Laboratory", resourcesDir);
    lab->AddDrawable(labDrawable);
    lab->SetRoot(labDrawable);
    lab->SetPosition(wxPoint(750, 785));
    picture->AddActor(lab);
    picture->SetLaboratoryDrawable(labDrawable);  // set laboratory for future reference


    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(750, 785));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(1100, 785));
    picture->AddActor(sparty);

    // Create and add Frank
    FrankFactory frankFactory;
    auto frank = frankFactory.Create(imagesDir);

    frank->SetPosition(wxPoint(300, 800));
    picture->AddActor(frank);

    return picture;
}

