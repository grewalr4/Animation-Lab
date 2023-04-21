/**
 * @file Winch.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Winch.h"

using namespace std;

/// Image for the winch panel in the rack
const std::wstring WinchBackgroundImage = L"/winch-12u-back.png";

/// Image for the winch handle (wheel)
const std::wstring WinchWheelImage = L"/winch-12u-wheel.png";

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

/// Wheel y-coord. adjustment
const int WheelYAdjustment = -65;

/**
 * Construct a winch
 * @param imagesDir Images directory
 */
Winch::Winch(std::wstring imagesDir)
        : Component(imagesDir), Equipment(), mMotionSource(this)
{
    mBackground.SetImage(GetImagesDir() + WinchBackgroundImage);
    mBackground.BottomCenteredRectangle();
    mWheel.SetImage(GetImagesDir() + WinchWheelImage);
    mWheel.CenteredSquare();  // allow rotation of wheel around center point
}

/**
 * Draw the winch
 * @param graphics Graphics context to render to
 * @param x X-coord.
 * @param y Y-coord.
 */
void Winch::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mBackground.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);
    mWheel.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y + WheelYAdjustment);
}

/**
 * Set the position
 * @param x x position
 * @param y y position
 * @param u u in the rack
 * @param xOffset x-offset in the rack
 */
void Winch::SetEquipmentPosition(int x, int y, int u, int xOffset)
{
    SetPosition(x + xOffset, y - u*RackUPixels - RackPixelsBelowFirstSlot);
}

/**
 * Facilitate physical movement of components
 * @param duration Duration to move for
 */
void Winch::Move(double duration)
{
    mMotionSource.Move(duration);
}

/**
 * Handle an animation XML event
 * @param node Node with animation details
 */
void Winch::XmlEvent(wxXmlNode* node)
{
    if (!mMoving)
    {
        mRotationAngle = stod(node->GetAttribute("rotate-to").ToStdWstring());
        mDuration = stod(node->GetAttribute("duration").ToStdWstring());
        mRotationRate = mRotationAngle / mDuration;
        mMoving = true;  // sentinel flag to prevent redundant movement
    }
}

/**
 * Update the winch
 * @param time Time to update
 */
void Winch::Update(double time)
{
    double elapsed = abs(GetTime() - time);
    if (mDuration > 0)
    {
        if (elapsed > mDuration)
        {
            elapsed = mDuration;  // stop over-rotation
        }
        mWheel.SetRotation(mWheel.GetRotation() + mRotationRate * elapsed);
        mDuration -= elapsed;
    }
    Component::Update(time);  // clock the current time for future reference
    Move(mDuration);  // render motion in the motion sink
}
