/**
 * @file Equipment.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_EQUIPMENT_H
#define CANADIANEXPERIENCE_EQUIPMENT_H

/**
 * Interface for equipment that can be mounted in an equipment rack
 */
class Equipment {
private:

protected:
    Equipment() {}

public:

    /// Destructor
    virtual ~Equipment() = default;

    /// Copy constructor/disabled
    Equipment(const Equipment&) = delete;

    /// Assignment operator/disabled
    void operator=(const Equipment&) = delete;

    /**
     * Set the position
     * @param x x position
     * @param y y position
     * @param u u in the rack
     * @param xOffset x-offset in the rack
     */
    virtual void SetEquipmentPosition(int x, int y, int u, int xOffset=0) = 0;

};

#endif //CANADIANEXPERIENCE_EQUIPMENT_H
