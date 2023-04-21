/**
 * @file ZPM.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "ZPM.h"
#include <sstream>

using namespace std;

/// The image to use for the ZPM
const std::wstring ZpmImage = L"/zpm.png";

/// The ZPM output voltage
const double ZPMVoltage = 1000;

/// The ZPM starting current
const double ZPMCurrent = 0;

/// X offset relative to the bottom center of the
/// ZPM image to where the statistics are displayed
const int StatsOffsetX = -22;

/// Y offset to where to draw the voltage in pixels
const int VoltageOffsetY = -70;

/// Y offset to where to draw the current in pixels
const int CurrentOffsetY = -50;

/// Location of the source on the ZPM
const wxPoint ZPMSourcePosition = wxPoint(20, -15);

/**
 * Construct a ZPM
 * @param imagesDir Images Directory
 */
ZPM::ZPM(std::wstring imagesDir)
        : Component(imagesDir), mSource(imagesDir, this)
{
    //
    // Default value handling
    //
    SetVoltage(ZPMVoltage);
    SetCurrent(ZPMCurrent);

    //
    // Prepare for drawing
    //
    if (GetImagesDir() != L"test")
    {
        SetImage(ZpmImage);
        BottomCenteredRectangle();
    }

    //
    // Set the source position
    //
    mSource.SetPosition(ZPMSourcePosition);
}

/**
 * Draw the component at the currently specified location
 * @param graphics Graphics object to render to
 * @param x X location
 * @param y Y location
 */
void ZPM::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mPolygon.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);
    graphics->SetPen(*wxWHITE_PEN);
    wxFont valFont(wxSize(0, 20),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(valFont, *wxWHITE);

    //
    // Draw the voltage
    //
    std::wstringstream str1;
    str1 << GetVoltage();
    graphics->DrawText(str1.str(), x + GetPosition().x + StatsOffsetX, y + GetPosition().y + VoltageOffsetY);

    //
    // Draw the current
    //
    std::wstringstream str2;
    str2 << GetCurrent();
    graphics->DrawText(str2.str(), x + GetPosition().x + StatsOffsetX, y + GetPosition().y + CurrentOffsetY);

    //
    // Draw the source fitting
    //
    mSource.Draw(graphics, x, y);
}

/**
 * Facilitate the movement of power
 * @param voltage Voltage
 * @return current
 */
double ZPM::Power(double voltage)
{
    double current = mSource.Power(voltage);
    SetCurrent(current);
    return current;
}

/**
 * Update the ZPM
 * @param time Time to update to
 */
void ZPM::Update(double time)
{
    Power(GetVoltage());
}
