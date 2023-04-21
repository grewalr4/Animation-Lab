/**
 * @file PowerSink.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "PowerSink.h"
#include "PowerSource.h"

using namespace std;

/// Image to use for power connections
const std::wstring ConnectionImage = L"/fitting.png";

/// Smallest size to display the connection
const int ConnectionMinimumSize = 10;

/// Used to compute the size of the connection image.
const int ConnectionCapacityDivisor = 100;

/**
 * Construct a power sink
 * @param imagesDir Images directory
 * @param component Component this is connected to
 */
PowerSink::PowerSink(std::wstring imagesDir, Component* component) : mComponent(component)
{

    if (imagesDir != L"test")
    {
        mPolygon.SetImage(imagesDir + ConnectionImage);
    }

}

/**
 * Facilitate the movement of power
 * @param voltage Voltage
 * @return current
 */
double PowerSink::Power(double voltage)
{
    return mComponent->Power(voltage);
}

/**
 * Set the source for this sink
 * @param source Source to set
 */
void PowerSink::SetSource(PowerSource* source)
{
    mSource = source;
    mSize = (mSource == nullptr) ? 0 : ConnectionMinimumSize + GetSource()->GetCurrent() / ConnectionCapacityDivisor;
    mPolygon.Rectangle(-mSize/2, 0, mSize, mSize);
}

/**
 * Draw this power sink
 * @param graphics Graphics context to render to
 * @param x X-coord.
 * @param y Y-coord.
 */
void PowerSink::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mPolygon.SetRotation(GetRotation());
    mPolygon.DrawPolygon(graphics, x + GetComponent()->GetPosition().x + GetPosition().x,
            y + GetComponent()->GetPosition().y + GetPosition().y);
}
