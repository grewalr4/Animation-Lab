/**
 * @file Laboratory1Factory.cpp
 * @author Ravi Grewal
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Laboratory1Factory.h"
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

using namespace std;

/**
 * Constructor
 * @param resourcesDir Path to program resources directory
 * @param imagesDir Path to the images directory
 */
Laboratory1Factory::Laboratory1Factory(std::wstring resourcesDir, std::wstring imagesDir)
        : mResourcesDir(resourcesDir), mImagesDir(imagesDir)
{

}

/**
 * Create the laboratory object
 * @return Laboratory object
 */
std::shared_ptr<WorkingLaboratory> Laboratory1Factory::Create()
{

    auto laboratory = make_shared<WorkingLaboratory>(1);

    // The laboratory background image
    auto background = make_shared<Shape>(mImagesDir);
    background->SetImage(L"/laboratory.jpg");
    background->Rectangle(-600, 0);
    laboratory->AddComponent(background);

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

    auto panel = make_shared<Shape>(mImagesDir);
    panel->SetImage( L"/vertical-panel.png");
    panel->Rectangle(Rack1X-99, RackY);
    laboratory->AddComponent(panel);

    // Convenience function in Rack that adds panels to the rack
    // at the right location.
    rack1->AddBlankPanel(L"/2u.png", 0);
    rack1->AddBlankPanel(L"/2u.png", 2);
    rack1->AddBlankPanel(L"/1u.png", 4);
    rack1->AddBlankPanel(L"/12u.png", 11);
    rack1->AddBlankPanel(L"/6u.png", 29);

    // Rack 2 - the right rack
    auto rack2 = make_shared<EquipmentRack>(mImagesDir);
    rack2->SetPosition(Rack2X, RackY);
    laboratory->AddComponent(rack2);

    rack2->AddBlankPanel(L"/5u.png", 0);
    rack2->AddBlankPanel(L"/radio-6u.png", 17);
    rack2->AddBlankPanel(L"/6u.png", 23);
    rack2->AddBlankPanel(L"/6u.png", 29);

    //
    // Zero-point Module
    //
    auto zpm = make_shared<ZPM>(mImagesDir);
    zpm->SetPosition(-550, -130);
    laboratory->AddComponent(zpm);
    laboratory->AddZPM(zpm);

    //
    // Distribution panels
    //
    auto distribution1 = make_shared<DistributionPanel>(mImagesDir, 1000);
    distribution1->AddSource(100);
    distribution1->AddSource(200);
    distribution1->AddSource(500);

    rack1->SetPanelPosition(distribution1, 5);
    laboratory->AddComponent(distribution1);

    auto distribution2 = make_shared<DistributionPanel>(mImagesDir, 100);
    distribution2->AddSource(100);
    distribution2->AddSource(100);

    rack1->SetPanelPosition(distribution2, 23);
    laboratory->AddComponent(distribution2);

    //
    // Switches
    //
    auto switch1 = make_shared<Switch>(mImagesDir, 100);
    switch1->SetName(L"switch1");
    rack1->SetPanelPosition(switch1, 11, -25);
    laboratory->AddComponent(switch1);
    switch1->SetPowerLocations();

    auto switch2 = make_shared<Switch>(mImagesDir, 200, true);
    switch2->SetName(L"switch2");
    rack1->SetPanelPosition(switch2, 11, 25);
    laboratory->AddComponent(switch2);
    switch2->SetPowerLocations(false);

    //
    // Lights
    //
    auto light1 = make_shared<Light>(mImagesDir, L"/light1.png", L"/light1on.png", 200);
    light1->SetPosition(180, -450);
    auto light1sink = light1->GetSink();
    light1sink->SetRotation(0.33);
    light1sink->SetPosition(wxPoint(-42, -70));
    laboratory->AddComponent(light1);

    auto light2 = make_shared<Light>(mImagesDir, L"/light2.png", L"/light2on.png", 100);
    light2->SetPosition(-250, -450);
    auto light2sink = light2->GetSink();
    light2sink->SetRotation(0.12);
    light2sink->SetPosition(wxPoint(-35, -13));
    laboratory->AddComponent(light2);

    auto light3 = make_shared<Light>(mImagesDir,
            L"/floor-lamp-off.png", L"/floor-lamp-on.png", 32);
    light3->SetPosition(Rack1X+120, -130);
    auto light3sink = light3->GetSink();
    light3sink->SetRotation(0.25);
    light3sink->SetPosition(wxPoint(-2, -15));
    laboratory->AddComponent(light3);

    auto light4 = make_shared<Light>(mImagesDir,
            L"/floor-lamp-off.png", L"/floor-lamp-on.png", 32);
    light4->SetPosition(Rack1X+150, -130);
    auto light4sink = light3->GetSink();
    light4sink->SetRotation(0.25);
    light4sink->SetPosition(wxPoint(-2, -15));
    laboratory->AddComponent(light3);


    //
    // Winch and orbs
    //

    auto winch = make_shared<Winch>(mImagesDir);
    winch->SetName(L"winch");
    rack2->SetPanelPosition(winch, 5);
    laboratory->AddComponent(winch);

    auto orbs = make_shared<SparkingOrb>(mImagesDir);
    orbs->SetPosition(-50, -700);
    laboratory->AddComponent(orbs);

    winch->GetMotionSource()->SetSink(orbs->GetMotionSink());

    //
    // Cables
    //

    // A factory makes it easier to avoid repeated code
    // when creating cables.
    CableFactory cableFactory(laboratory, mImagesDir);

    // ZPM to distribution1
    /*
     *
     * Test distribution panel
    auto cable = cableFactory.Create(zpm->GetSource(),
            distribution1->GetSink());
    cable = cableFactory.Create(distribution1->GetSource(1),
            light1->GetSink());
    cable = cableFactory.Create(distribution1->GetSource(2),
            light2->GetSink());
    cable = cableFactory.Create(distribution1->GetSource(3),
            light3->GetSink());
    */
    auto cable = cableFactory.Create(zpm->GetSource(),
            distribution1->GetSink());

    // Distribution to switch1
    cable = cableFactory.Create(distribution1->GetSource(1),
            switch1->GetSink(),
            30, 10);
    cable->AddClamp(Rack1X-80, -280, 0, 50);

    // Switch 1 to distribution 2
    cable = cableFactory.Create(switch1->GetSource(true), distribution2->GetSink(),
            30, 30);

    // Switch 1 to light 3
    cable = cableFactory.Create(switch1->GetSource(false), light3->GetSink(),
            30, 30);

    cable->AddClamp(Rack1X-85, -250, 0.5, 50);
    cable->AddClamp(Rack1X-85, -180, 0.5, 70);

    // Distribution 2 source 1 to light 2
    cable = cableFactory.Create(distribution2->GetSource(1),
            light2->GetSink(),
            30, 20);

    cable->AddClamp(Rack1X-85, -470, 0, 50);
    cable->AddClamp(Rack1X-85, -500, 0, 100);

    // Distribution 2 to light 1
    cable = cableFactory.Create(distribution2->GetSource(2),
            light1->GetSink(),
            30, 20);

    cable->AddClamp(Rack1X-80, -470, 0, 50);
    cable->AddClamp(Rack1X-80, -550, 0, 100);

    // Distribution to switch2
    cable = cableFactory.Create(distribution1->GetSource(2),
            switch2->GetSink(),
            30, 10);
    cable->AddClamp(Rack1X+80, -280, 0, 50);

    // Switch 2 to Orbs
    cable = cableFactory.Create(switch2->GetSource(true),
            orbs->GetSink());


    // The bed
    auto bed = make_shared<Shape>(mImagesDir);
    bed->SetImage(L"/bed.png");
    int wid = 400;
    bed->Rectangle(-wid/2, -10, wid);
    laboratory->AddComponent(bed);

    // Load the script
    laboratory->LoadScript(mResourcesDir + L"/scripts/laboratory1.xml");

    return laboratory;
}