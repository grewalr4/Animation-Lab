/**
 * @file PowerSource.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "PowerSource.h"
#include "PowerSink.h"

using namespace std;

/// Image to use for power connections
const std::wstring ConnectionImage = L"/fitting.png";

/// Smallest size to display the connection
const int ConnectionMinimumSize = 10;

/// Used to compute the size of the connection image.
const int ConnectionCapacityDivisor = 100;

/**
 * Construct a power source
 * @param imagesDir Images directory
 * @param component Component this source is connected to
 * @param current Current
 */
PowerSource::PowerSource(std::wstring imagesDir, Component* component, double current) : mComponent(component), mCurrent(current)
{

    if (imagesDir != L"test")
    {
        mPolygon.SetImage(imagesDir + ConnectionImage);
    }
    mSize = ConnectionMinimumSize + GetCurrent() / ConnectionCapacityDivisor;
    mPolygon.Rectangle(-mSize/2, 0, mSize, mSize);
}

/**
 * Facilitate the movement of power
 * @param voltage Voltage
 * @return current
 */
double PowerSource::Power(double voltage)
{
    return (mSink != nullptr) ? mSink->Power(voltage) : 0;
}

/**
 * Set the sink for this source
 * @param sink Sink to set
 */
void PowerSource::SetSink(PowerSink* sink)
{
    mSink = sink;
    sink->SetSource(this);
}

/**
 * Draw this power source
 * @param graphics Graphics context to render to
 * @param x X-coord.
 * @param y Y-coord.
 */
void PowerSource::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mPolygon.SetRotation(GetRotation());
    mPolygon.DrawPolygon(graphics, x + GetComponent()->GetPosition().x + GetPosition().x,
                y + GetComponent()->GetPosition().y + GetPosition().y);
}
