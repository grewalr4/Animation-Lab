/**
 * @file Laboratory2Factory.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Laboratory2Factory.h"
#include "WorkingLaboratory.h"
#include "Shape.h"
#include "EquipmentRack.h"
#include "ZPM.h"
#include "Light.h"
#include "Switch.h"
#include "DistributionPanel.h"
#include "Cable.h"
#include "CableFactory.h"
#include "SparkingOrb.h"
#include "Winch.h"
#include "ElectricWinch.h"
#include "Rheostat.h"
#include "RotarySwitch.h"

using namespace std;

/// Directory containing images within the resources
const std::wstring ImagesDirectory = L"/images";

/// Maximum number of sources
const int MaxSources = 11;


/**
 * Constructor
 * @param resourcesDir Path to program resources directory
 * @param imagesDir Path to the images directory
 */
Laboratory2Factory::Laboratory2Factory(std::wstring resourcesDir, std::wstring imagesDir)
        : mResourcesDir(resourcesDir), mImagesDir(imagesDir)
{

}

/**
 * Create the laboratory object
 * @return Laboratory object
 */
std::shared_ptr<WorkingLaboratory> Laboratory2Factory::Create()
{
    auto laboratory = make_shared<WorkingLaboratory>(2);

    // The laboratory background image
    auto background = make_shared<Shape>(mImagesDir);
    background->SetImage(L"/laboratory.jpg");
    background->Rectangle(-600, 0);
    laboratory->AddComponent(background);

    //
    // Zero-point Module
    //
    auto zpm = make_shared<ZPM>(mImagesDir);
    zpm->SetPosition(-550, -130);
    laboratory->AddComponent(zpm);
    laboratory->AddZPM(zpm);

    //
    // Two racks
    //
    const int Rack1X = -350;
    const int Rack2X = 350;
    const int RackY = -130;

    // Rack 1 - the left rack
    auto rack1 = make_shared<EquipmentRack>(mImagesDir);
    rack1->SetPosition(Rack1X, RackY);
    laboratory->AddComponent(rack1);

    // Rack 2 - the right rack
    auto rack2 = make_shared<EquipmentRack>(mImagesDir);
    rack2->SetPosition(Rack2X, RackY);
    laboratory->AddComponent(rack2);

    //
    // Lights
    //
    auto light1 = make_shared<Light>(mImagesDir, L"/light1.png", L"/light1on.png", 200);
    light1->SetPosition(180, -450);
    auto light1sink = light1->GetSink();
    light1sink->SetRotation(0.33);
    light1sink->SetPosition(wxPoint(-42, -70));
    laboratory->AddComponent(light1);

    //
    // Distribution panels
    //
    auto distribution1 = make_shared<DistributionPanel>(mImagesDir, 1000);
    distribution1->AddSource(100);
    distribution1->AddSource(200);
    distribution1->AddSource(500);

    rack1->SetPanelPosition(distribution1, 5);
    laboratory->AddComponent(distribution1);

    //
    // Electric Winch (challenge task #1)
    //
    auto electricWinch = make_shared<ElectricWinch>(mImagesDir);
    electricWinch->SetName(L"electricWinch");
    rack2->SetPanelPosition(electricWinch, 4);
    laboratory->AddComponent(electricWinch);

    //
    // Rheostat (challenge task #2)
    //
    auto rheostat = make_shared<Rheostat>(mImagesDir);
    rheostat->SetName(L"rheostat");
    rheostat->SetPosition(Rack1X+120, -130);
    laboratory->AddComponent(rheostat);

    //
    // Rotary Switch
    //
    auto rotarySwitch = make_shared<RotarySwitch>(mImagesDir, 0);
    rotarySwitch->SetName(L"rotarySwitch");
    rack1->SetPanelPosition(rotarySwitch, 18, -50);
    laboratory->AddComponent(rotarySwitch);

    //
    // Cables
    //
    CableFactory cableFactory(laboratory, mImagesDir);

    auto cable = cableFactory.Create(distribution1->GetSource(3),
            rotarySwitch->GetSink());
    
    //
    // Lights for rotary switch
    //
    for (int i = 0; i < MaxSources; ++i)
    {
        auto rotaryLight = make_shared<Light>(mImagesDir,
                L"/floor-lamp-off.png", L"/floor-lamp-on.png", 32);
        rotaryLight->SetPosition(Rack1X+i*20 + -85, -570);
        auto rotaryLightsink = rotaryLight->GetSink();
        rotaryLightsink->SetRotation(0.5);
        rotaryLightsink->SetPosition(wxPoint(-2, -10));
        laboratory->AddComponent(rotaryLight);
        auto cable = cableFactory.Create(rotarySwitch->GetSource(i),
                rotaryLightsink);
    }

    cable = cableFactory.Create(zpm->GetSource(),
            distribution1->GetSink());

    cable = cableFactory.Create(distribution1->GetSource(1),
            rheostat->GetSink(),
            30, 10);

    cable = cableFactory.Create(distribution1->GetSource(2),
            electricWinch->GetPowerSink(),
            30, 10);

    cable = cableFactory.Create(rheostat->GetSource(),
            light1->GetSink(),
            30, 10);

    // Load the script
    laboratory->LoadScript(mResourcesDir + L"/scripts/laboratory2.xml");


    return laboratory;
}
