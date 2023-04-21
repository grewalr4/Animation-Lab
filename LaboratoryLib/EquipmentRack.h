/**
 * @file EquipmentRack.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_EQUIPMENTRACK_H
#define CANADIANEXPERIENCE_EQUIPMENTRACK_H

#include "Shape.h"
#include "Equipment.h"

/**
 * An equipment rack that holds panels
 */
class EquipmentRack : public Shape {
private:

    /// The components in this rack
    std::vector<std::shared_ptr<Component>> mItems;

public:

    /// Destructor
    virtual ~EquipmentRack() = default;

    /// Copy constructor/disabled
    EquipmentRack(const EquipmentRack&) = delete;

    /// Assignment operator/disabled
    void operator=(const EquipmentRack&) = delete;

    EquipmentRack(std::wstring imagesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    /**
     * Add a blank panel to the rack
     * @param image for the panel
     * @param u units for panel
     */
    void AddBlankPanel(std::wstring image, int u);

    void SetPanelPosition(std::shared_ptr<Equipment> equipment, int u, int xOffset=0);

};

#endif //CANADIANEXPERIENCE_EQUIPMENTRACK_H
