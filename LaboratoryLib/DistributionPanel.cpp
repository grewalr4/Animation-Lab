/**
 * @file DistributionPanel.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "DistributionPanel.h"
#include "EquipmentRack.h"

using namespace std;

/// The image to use for the distribution panel
const std::wstring DistributionImage = L"/dist-6u.png";

/// Y location for the sources in pixels
const int SourcesY = -35;

/// X location for the first source in pixels
const int SourcesX = -35;

/// Spacing between the sources in pixels
const int SourcesSpacing = 15;

/// Location of the sink on the
const wxPoint DistributionSinkPosition = wxPoint(-48, -20);

/// Rotation of the sink
const double DistributionSinkRotation = -0.25;

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

/**
 * Construct a distribution panel
 * @param imagesDir Images directory
 * @param voltage Voltage
 */
DistributionPanel::DistributionPanel(std::wstring imagesDir, double voltage) : Component(imagesDir),
    Equipment(), mSink(imagesDir, this)
{
    SetVoltage(voltage);
    mPolygon.SetImage(GetImagesDir() + DistributionImage);
    mPolygon.Rectangle(-RackPanelWidthPixels/2, 0);
    mSink.SetPosition(DistributionSinkPosition);
    mSink.SetRotation(DistributionSinkRotation);
}

/**
 * Draw a distribution panel
 * @param graphics Graphics context to render to
 * @param x X-coord.
 * @param y Y-coord.
 */
void DistributionPanel::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mPolygon.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);
    mSink.Draw(graphics, x, y);
    for (auto source : mSources)
    {
        source->Draw(graphics, x, y);
    }
}

void DistributionPanel::SetEquipmentPosition(int x, int y, int u, int xOffset)
{
    SetPosition(x + xOffset, y - u*RackUPixels - RackPixelsBelowFirstSlot);
}

/**
 * Add a source to the distribution panel
 * @param current current for the source (used to draw cables/fittings)
 */
void DistributionPanel::AddSource(double current)
{
    mSources.push_back(make_shared<PowerSource>(GetImagesDir(), this, current));
    int sourceNum = mSources.size() - 1;
    mSources[sourceNum]->SetPosition(wxPoint(SourcesX + SourcesSpacing*sourceNum, SourcesY));
}

/**
 * Supply voltage to this component.
 * @param voltage Voltage supplied in volts
 * @return Amperage consumed by the component.
 */
double DistributionPanel::Power(double voltage)
{
    double current = 0;
    for (auto source : mSources)
    {
        current += source->Power(voltage);
    }
    return current;
}
