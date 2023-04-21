/**
 * @file WorkingLaboratory.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "WorkingLaboratory.h"
#include "LaboratoryActual.h"
#include "Component.h"
#include "ZPM.h"
#include "Event.h"

using namespace std;

/**
 * Create a working laboratory
 * @param laboratoryNumber the number for this lab
 */
WorkingLaboratory::WorkingLaboratory(int laboratoryNumber) : mLaboratoryNumber(laboratoryNumber)
{

}

/**
 * Add a component to the laboratory
 * @param component
 */
void WorkingLaboratory::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
    component->SetLaboratory(this);
}

/**
 * Draw the contents of the working laboratory
 * @param graphics Graphics context to render to
 * @param x X-coord.
 * @param y Y-coord.
 */
void WorkingLaboratory::DrawLaboratory(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    for (auto component : mComponents)
    {
        component->Draw(graphics, x, y);
    }
}

/**
 * Get the location of the laboratory
 * @return wxPoint location
 */
wxPoint WorkingLaboratory::GetLocation()
{
    return GetLaboratoryActual()->GetLocation();
}

/**
 * Add a ZPM to the laboratory
 * @param zpm ZPM to add
 */
void WorkingLaboratory::AddZPM(std::shared_ptr<ZPM> zpm)
{
    mZPM = zpm;
    // two-sided association handled by AddComponent function
}

/**
 * Update all of the components
 * @param time Time to update to
 */
void WorkingLaboratory::Update(double time)
{
    Animate(time);  // handle event animations
    for (auto component : mComponents)
    {
        component->Update(time);
    }
}

/**
 * Load animation events
 * @param path path to XML file
 */
void WorkingLaboratory::LoadScript(std::wstring path)
{
    if (!mXmlDoc.Load(path))
    {
        wxMessageBox(L"Unable to load laboratory script: " + path);
        return;
    }

    auto rootNode = mXmlDoc.GetRoot();  // Get the XML document root node
    auto eventNode = rootNode->GetChildren();
    for( ; eventNode; eventNode = eventNode->GetNext())
    {
        double time = stod(eventNode->GetAttribute("time").ToStdWstring());
        wstring target = eventNode->GetAttribute("target").ToStdWstring();
        auto event = make_shared<Event>(target, eventNode, time);
        mEvents.push_back(event);
    }

}

/**
 * Animate the laboratory
 * @param time Current time
 */
void WorkingLaboratory::Animate(double time)
{
    int nextEvent = 0;
    //
    // Send any events that become active to the components
    //
    while (nextEvent < mEvents.size() && mEvents[nextEvent]->GetTime() <= time)
    {
        // Process this event
        auto event = mEvents[nextEvent];

        for (auto component : mComponents)
        {
            if(component->GetName() == event->GetTarget())
            {
                component->XmlEvent(event->GetNode());
            }
        }

        nextEvent++;
    }
}
