/**
 * @file SparkingOrb.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "SparkingOrb.h"
#include "WorkingLaboratory.h"

using namespace std;

/// The image for the orbs
const std::wstring OrbsImage = L"/orbs.png";

/// Orb voltage for full power
const double OrbsVoltage = 1000;

/// Voltage below which the orbs do not spark.
const double OrbsMinVoltage = 250;

/// Orb amperage at full voltage
const double OrbsCurrent = 200;

/// Position on the Orbs where the power is connected
const wxPoint OrbsSinkPosition = wxPoint(-132, -110);

/// X offset to the left orb spark end in pixels
const int SparkOffset1X = -72;

/// X offset to the right orb spark end in pixels
const int SparkOffset2X = 75;

/// Y offset for the orb spark ends
const int SparkOffsetY = -45;

/// Intensity for spark
const double SparkyIntensity = 1.0;

/// Motion distance
const double OrbsMovementDistance = 20.0;

/**
 * Construct a sparking orb
 * @param imagesDir Images directory to use
 */
SparkingOrb::SparkingOrb(std::wstring imagesDir)
        : Component(imagesDir), mSink(imagesDir, this), mMotionSink(this)
{
    mPolygon.SetImage(GetImagesDir() + OrbsImage);
    mPolygon.BottomCenteredRectangle();
    mSink.SetPosition(OrbsSinkPosition);
    mSparky.SetIntensity(SparkyIntensity);
}

/**
 * Draw the orbs at the currently specified location
 * @param graphics Graphics object to render to
 * @param x X location
 * @param y Y location
 */
void SparkingOrb::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mPolygon.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);
    mSink.Draw(graphics, x, y);
    if (mSpark)
    {
        // graphics->SetPen(*wxWHITE_PEN);
        // graphics->StrokeLine(x + GetPosition().x + SparkOffset1X, y + GetPosition().y + SparkOffsetY, x + GetPosition().x + SparkOffset2X, y + GetPosition().y + SparkOffsetY);
        mSparky.Draw(graphics, x + GetPosition().x + SparkOffset1X, y + GetPosition().y + SparkOffsetY, x + GetPosition().x + SparkOffset2X, y + GetPosition().y + SparkOffsetY);
    }
}

/**
 * Handle movement of electricity
 * @param voltage
 * @return current
 */
double SparkingOrb::Power(double voltage)
{
    double current = voltage / OrbsVoltage * OrbsCurrent;
    if (voltage > OrbsMinVoltage)
    {
        mSpark = true;
    }
    else
    {
        mSpark = false;
        mSparky.Reset();
    }
    return current;
}

/**
 * Update the component
 * @param time Time used in the update
 */
void SparkingOrb::Update(double time)
{
    double elapsed = abs(GetTime() - time);
    if (mDuration > 0)
    {
        if (elapsed > mDuration)
        {
            elapsed = mDuration;  // stop over-rotation
        }
        SetPosition(GetPosition().x, GetPosition().y + (mDistance/mDuration) * elapsed);
        mDuration -= elapsed;
    }
    Component::Update(time);  // clock the current time for future reference
    mSparky.Update(time);
}

/**
 * Move the sparking orb
 * @param duration Duration to move for
 */
void SparkingOrb::Move(double duration)
{
    mDuration = duration;
    mDistance = OrbsMovementDistance;
}
