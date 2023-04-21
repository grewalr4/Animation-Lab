/**
 * @file Light.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Light.h"

/// Light voltage for full illumination
const double LightVoltage = 1000;

/// Light amperage at full voltage
const double LightCurrent = 100;

/// Input position for floor lamp
const wxPoint FloorLampInput = {-2, -15};

/// Rotation for floor lamp
const double FloorLampRotation = 0.25;

/// Input position for light 1
const wxPoint Light1Input = {-42, -70};

/// Rotation for light 1
const double Light1Rotation = 0.33;

/// Input position for light 2
const wxPoint Light2Input = {-35, -13};

/// Rotation for light 2
const double Light2Rotation = 0.12;

/// Orb voltage for full power
const double OrbsVoltage = 1000;

/**
 * Construct a light
 * @param imagesDir Images directory
 * @param backgroundImage Background image
 * @param lightImage Light image
 * @param width Width of the light
 */
Light::Light(std::wstring imagesDir, std::wstring backgroundImage, std::wstring lightImage, int width)
        : Component(imagesDir), mSink(imagesDir, this)
{
    mBackgroundPolygon.SetImage(imagesDir + backgroundImage);
    mBackgroundPolygon.Rectangle(-width/2, 0, width);
    mLightPolygon.SetImage(imagesDir + lightImage);
    mLightPolygon.Rectangle(-width/2, 0, width);
}

/**
 * Draw the light at the currently specified location
 * @param graphics Graphics object to render to
 * @param x X location
 * @param y Y location
 */
void Light::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mBackgroundPolygon.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);
    if (mIsOn)
    {
        mLightPolygon.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);
    }
    mSink.Draw(graphics, x, y);
}

/**
 * Facilitate the movement of power
 * @param voltage Voltage
 * @return current
 */
double Light::Power(double voltage)
{
    double current = voltage / LightVoltage * LightCurrent;
    if (voltage > 0)
    {
        mLightPolygon.SetOpacity(voltage / OrbsVoltage);
        mIsOn = true;
    }
    else
    {
        mIsOn = false;
    }
    return current;
}


