/**
 * @file ElectricWinch.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "ElectricWinch.h"

/// Electric Winch sink position
const wxPoint ElectricWinchSinkPosition = wxPoint(-40, -20);

/// Electric Winch sink rotation
const double ElectricWinchRotation = -0.25;

/// Electric Winch voltage for full power
const double ElectricWinchVoltage = 1000;

/// Electric Winch amperage at full power
const double ElectricWinchCurrent = 100;

using namespace std;

/**
 * Construct an electric winch
 * @param imagesDir Images directory
 */
ElectricWinch::ElectricWinch(std::wstring imagesDir) : Winch(imagesDir), mPowerSink(imagesDir, this)
{
    mPowerSink.SetPosition(ElectricWinchSinkPosition);
    mPowerSink.SetRotation(ElectricWinchRotation);
}

/**
 * Draw the electric winch (and its power sink)
 * @param graphics Graphic context to render to
 * @param x x-location
 * @param y y-location
 */
void ElectricWinch::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    Winch::Draw(graphics, x, y);
    mPowerSink.Draw(graphics, x, y);
}

/**
 * Facilitate the movement of power
 * @param voltage Voltage this winch is receiving
 * @return current
 */
double ElectricWinch::Power(double voltage)
{
    double current = voltage / ElectricWinchVoltage * ElectricWinchCurrent;
    mOn = (voltage > 0) ? true : false;
    return current;
}

/**
 * Update this electric winch
 * @param time Time to update to
 */
void ElectricWinch::Update(double time)
{
    if (mOn)
    {
        Winch::Update(time);
    }
}