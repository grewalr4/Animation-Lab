/**
 * @file Switch.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Switch.h"

using namespace std;

/// The image to use for the switch on
const std::wstring SwitchOnImage = L"/knifeswitch-on.png";

/// The image to use for the switch on
const std::wstring SwitchOffImage = L"/knifeswitch-off.png";

/// X location for connections for the left side of the switch
const int SwitchLeftX = -22;

/// X location for connections for the right side of the switch
const int SwitchRightX = 22;

/// Y location for sink
const int SwitchSinkY = -63;

/// Y position for the switch down source
const int SwitchSource0Y = -37;

/// Y position for the switch up source
const int SwitchSource1Y = -89;

/// Switch width
const int SwitchWidth = 50;

/// Width of the rack panel in inches
const double RackPanelWidth = 19;

/// Height of a rack unit in inches
const double RackUnit = 1.75;

/// Total width to draw the rack
const int RackWidthPixels = 131;

/// Width of a rack panel in pixels
const int RackPanelWidthPixels = 113;

/// Pixels per inch in the rack image
const double RackPixelsPerInch = RackPanelWidthPixels / RackPanelWidth;

/// A single U size in pixels
const double RackUPixels = RackPixelsPerInch * RackUnit;

/// The number of pixels below the bottom of the first
/// rack slot (unit)
const double RackPixelsBelowFirstSlot = 15;

/// Source and sink rotations
const double SwitchRotation = 0.25;

/**
 * Construct a switch
 * @param imagesDir Images directory
 * @param amperage Current
 * @param isOn Is switch on?
 */
Switch::Switch(std::wstring imagesDir, int amperage, bool isOn) : Component(imagesDir),
    mOnSource(imagesDir, this), mOffSource(imagesDir, this), mSink(imagesDir, this), mIsOn(isOn)
{
    SetCurrent(amperage);

    if (imagesDir != L"test")
    {
        mOnPolygon.SetImage(GetImagesDir() + SwitchOnImage);
        mOffPolygon.SetImage(GetImagesDir() + SwitchOffImage);
        mOnPolygon.BottomCenteredRectangle();
        mOffPolygon.BottomCenteredRectangle();
    }

}

/**
 * Draw the switch
 * @param graphics Graphics context to render to
 * @param x X-coord.
 * @param y Y-coord.
 */
void Switch::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    if (mIsOn)
    {
        mOnPolygon.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);
    }
    else
    {
        mOffPolygon.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);
    }

    //
    // Draw the sources and sink
    //
    mOnSource.Draw(graphics, x, y);
    mOffSource.Draw(graphics, x, y);
    mSink.Draw(graphics, x, y);
}

/**
 * Facilitate the movement of power
 * @param voltage Voltage
 * @return current
 */
double Switch::Power(double voltage)
{
    if (mIsOn)
    {
        mOffSource.Power(0);
        return mOnSource.Power(voltage);
    }
    else
    {
        mOnSource.Power(0);
        return mOffSource.Power(voltage);
    }
}

/**
  * Handle an animation XML event
  * @param node Node with animation details
  */
void Switch::XmlEvent(wxXmlNode* node)
{
    auto on = node->GetAttribute("on").ToStdWstring();
    mIsOn = (on == "true") ? true : false;
}

void Switch::SetEquipmentPosition(int x, int y, int u, int xOffset)
{
    SetPosition(x + xOffset, y - u*RackUPixels - RackPixelsBelowFirstSlot);
}

/**
 * Set the locations for the sink and sources
 * @param isLeft is this switch on the left or right?
 */
void Switch::SetPowerLocations(bool isLeft)
{
    double xPos = (isLeft) ? SwitchLeftX : SwitchRightX;
    double rotation = (isLeft) ? -SwitchRotation : SwitchRotation;

    //
    // Set source and sink positions
    //
    mOnSource.SetPosition(wxPoint(xPos, SwitchSource1Y));
    mOffSource.SetPosition(wxPoint(xPos, SwitchSource0Y));
    mSink.SetPosition(wxPoint(xPos, SwitchSinkY));

    //
    // Set source and sink rotations
    //
    mOnSource.SetRotation(rotation);
    mOffSource.SetRotation(rotation);
    mSink.SetRotation(rotation);

}


