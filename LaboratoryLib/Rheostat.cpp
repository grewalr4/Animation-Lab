/**
 * @file Rheostat.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Rheostat.h"

using namespace std;

/// Image file for rheostat background
const std::wstring RheostatBackgroundImage = L"/rheostat.png";

/// Image file for rheostat knob
const std::wstring RheostatKnobImage = L"/rheostat-knob.png";

/// Adjustment for knob image in y-direction
const int KnobYAdjustment = -50;

/// Adjustment for knob image in x-direction
const int KnobXAdjustment = 40;

/// Rheostat sink position
const wxPoint RheostatSinkPosition = {0, -50};

/// Rheostat source position
const wxPoint RheostatSourcePosition = {100, -50};

/// Width of rheostat background polygon
const int RheostatWidth = 100;

/// Scale for knob
const int RheostatKnobScale = 75;

/// Source rotation
const double RheostatSourceRotation = 0.25;

/// Sink rotation
const double RheostatSinkRotation = -0.25;

/// Rheostat gauge multiplier
const int RheostatGaugeMultiplier = 2;

/// Rheostat max rotation
const double RheostatMaxRotation = 0.5;

/**
 * Construct a rheostat
 * @param imagesDir Images directory
 */
Rheostat::Rheostat(std::wstring imagesDir)
        : Component(imagesDir), mSource(imagesDir, this), mSink(imagesDir, this)
{
    mBackground.SetImage(GetImagesDir() + RheostatBackgroundImage);
    mBackground.Rectangle(0, 0, RheostatWidth);
    mKnob.SetImage(GetImagesDir() + RheostatKnobImage);
    mKnob.CenteredSquare(RheostatKnobScale);  // allow rotation of knob around center point

    mSource.SetPosition(RheostatSourcePosition);
    mSource.SetRotation(RheostatSourceRotation);
    mSink.SetPosition(RheostatSinkPosition);
    mSink.SetRotation(RheostatSinkRotation);
}

/**
 * Draw the rheostat
 * @param graphics Graphics context to render to
 * @param x X-coord.
 * @param y Y-coord.
 */
void Rheostat::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mBackground.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);
    mKnob.DrawPolygon(graphics, x + GetPosition().x + KnobXAdjustment, y + GetPosition().y + KnobYAdjustment);
    mSource.Draw(graphics, x, y);
    mSink.Draw(graphics, x, y);
}

/**
 * Handle an animation XML event
 * @param node Node with animation details
 */
void Rheostat::XmlEvent(wxXmlNode* node)
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
 * Update the rheostat
 * @param time Time to update to
 */
void Rheostat::Update(double time)
{
    double elapsed = abs(GetTime() - time);
    if (mDuration > 0)
    {
        if (elapsed > mDuration)
        {
            elapsed = mDuration;  // stop over-rotation
        }
        mCurrentRotation = mKnob.GetRotation() + mRotationRate * elapsed;
        if (mCurrentRotation > RheostatMaxRotation)
        {
            mCurrentRotation = 0.5;  // set a maximum rotation allowed
        }
        mKnob.SetRotation(mCurrentRotation);
        mDuration -= elapsed;
    }
    Component::Update(time);  // clock the current time for future reference
}

/**
 * Facilitate the movement of power
 * @param voltage Voltage
 * @return current
 */
double Rheostat::Power(double voltage)
{
    return mSource.Power(voltage * mCurrentRotation * RheostatGaugeMultiplier);
}
