/**
 * @file EquipmentRack.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "EquipmentRack.h"

using namespace std;

/// The rack image
const std::wstring RackImage = L"/rack.png";

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
 * Construct an equipment rack
 * @param imagesDir Images directory
 */
EquipmentRack::EquipmentRack(std::wstring imagesDir) : Shape(imagesDir)
{
    SetImage(RackImage);
    Rectangle(-RackWidthPixels/2, 0, RackWidthPixels);
}

/**
 * Draw an equipment rack
 * @param graphics Graphics context to render to
 * @param x X-coord.
 * @param y Y-coord.
 */
void EquipmentRack::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    Shape::Draw(graphics, x, y);

    //
    // Draws the items inside the rack
    //
    for (auto item : mItems)
    {
        item->Draw(graphics, x, y);
    }
}

void EquipmentRack::AddBlankPanel(std::wstring image, int u)
{
    auto blankPanel = make_shared<Shape>(GetImagesDir());
    blankPanel->SetImage(image);
    blankPanel->Rectangle(-RackPanelWidthPixels/2, 0);
    blankPanel->SetPosition(GetPosition().x, GetPosition().y - u*RackUPixels - RackPixelsBelowFirstSlot);
    mItems.push_back(blankPanel);
}

/**
 * Set the equipment's panel position
 * @param equipment equipment that is being mounted in the rack
 * @param u Units in rack
 * @param xOffset the X-offset
 */
void EquipmentRack::SetPanelPosition(std::shared_ptr<Equipment> equipment, int u, int xOffset)
{
    equipment->SetEquipmentPosition(GetPosition().x, GetPosition().y, u, xOffset);
}


