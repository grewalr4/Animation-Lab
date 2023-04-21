/**
 * @file RotarySwitch.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "RotarySwitch.h"

using namespace std;

/// Maximum number of sources
const int MaxSources = 11;

/// Panel image
const std::wstring PanelImage = L"/12u.png";

/// Rail image
const std::wstring RailImage = L"/source-rail.png";

/// Switch image
const std::wstring SwitchImage = L"/rheostat.png";

/// Knob image
const std::wstring KnobImage = L"/rheostat-knob.png";

/// Width of rheostat background polygon
const int RheostatWidth = 100;

/// Scale for knob
const int RheostatKnobScale = 75;

/// Adjustment for knob image in y-direction
const int KnobYAdjustment = -50;

/// Adjustment for knob image in x-direction
const int KnobXAdjustment = 43;

/// Y location for the sources in pixels
const int SourcesY = -110;

/// X location for the first source in pixels
const int SourcesX = 4;

/// Spacing between the sources in pixels
const int SourcesSpacing = 9;

/// Rotation of the sink
const double SinkRotation = -0.25;

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

/// Panel x-adjustment
const int PanelXAdjustment = 50;

/// Panel y-adjustment
const int PanelYAdjustment = 50;

/// Rail x-adjustment
const int RailXAdjustment = 50;

/// Rail y-adjustment
const int RailYAdjustment = -100;

/// Sink position
const wxPoint SinkPosition = {2, -105};

/// Degrees to normalize knob
const double Degrees = 188.0;

/**
 *
 * @param imagesDir
 * @param sourceNum
 */
RotarySwitch::RotarySwitch(std::wstring imagesDir, int sourceNum) : mSourceNum(sourceNum), Component(imagesDir), mSink(imagesDir, this)
{
    mPanel.SetImage(GetImagesDir() + PanelImage);
    mRail.SetImage(GetImagesDir() + RailImage);
    mSwitch.SetImage(GetImagesDir() + SwitchImage);
    mKnob.SetImage(GetImagesDir() + KnobImage);

    mRail.BottomCenteredRectangle();
    mPanel.BottomCenteredRectangle();
    mSwitch.Rectangle(0, 0, RheostatWidth);
    mKnob.CenteredSquare(RheostatKnobScale);  // allow rotation of knob around center point

    //
    // Prepare the sinks and sources
    //
    mSink.SetPosition(SinkPosition);
    mSink.SetRotation(SinkRotation);
    for (int i = 0; i < MaxSources; ++i)
    {
        mSources.push_back(make_shared<PowerSource>(imagesDir, this));
        mSources[i]->SetPosition(wxPoint(SourcesX + i*SourcesSpacing, SourcesY));
    }
}

/**
 * Draw the rotary switch
 * @param graphics Graphics context to render to
 * @param x X-coord.
 * @param y Y-coord.
 */
void RotarySwitch::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    //
    // Drawing the rotary switch parts in proper order
    //
    mPanel.DrawPolygon(graphics, x + GetPosition().x + PanelXAdjustment, y + GetPosition().y);
    mSwitch.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);
    mKnob.DrawPolygon(graphics, x + GetPosition().x + KnobXAdjustment, y + GetPosition().y + KnobYAdjustment);
    mRail.DrawPolygon(graphics, x + GetPosition().x + RailXAdjustment, y + GetPosition().y + RailYAdjustment);


    //
    // Drawing sources and sink
    //
    mSink.Draw(graphics, x, y);
    for (int i = 0; i < MaxSources; ++i)
    {
        mSources[i]->Draw(graphics, x, y);
    }
}

/**
 * Set the position
 * @param x x position
 * @param y y position
 * @param u u in the rack
 * @param xOffset x-offset in the rack
 */
void RotarySwitch::SetEquipmentPosition(int x, int y, int u, int xOffset)
{
    SetPosition(x + xOffset, y - u*RackUPixels - RackPixelsBelowFirstSlot);
}

/**
 * Facilitate the movement of power
 * @param voltage Voltage to move
 * @return current
 */
double RotarySwitch::Power(double voltage)
{
    return mSources[mSourceNum]->Power(voltage);
}

/**
  * Handle an animation XML event
  * @param node Node with animation details
  */
void RotarySwitch::XmlEvent(wxXmlNode* node)
{
    auto position = stoi(node->GetAttribute("position").ToStdWstring());
    if (position < MaxSources)
    {
        mSources[mSourceNum]->Power(0);
        mSourceNum = position;
        mKnob.SetRotation(MaxSources/Degrees * position);
    }
}
