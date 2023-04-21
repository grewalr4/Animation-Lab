/**
 * @file Switch.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_SWITCH_H
#define CANADIANEXPERIENCE_SWITCH_H

#include "Component.h"
#include "Polygon.h"
#include "PowerSource.h"
#include "PowerSink.h"
#include "Equipment.h"

/**
 * Switch in the laboratory to distribute power
 */
class Switch : public Component, public Equipment {
private:

    /// Switch on?
    bool mIsOn = false;

    /// Polygon for on-switch
    cse335::Polygon mOnPolygon;

    /// Polygon for off-switch
    cse335::Polygon mOffPolygon;

    /// On source
    PowerSource mOnSource;

    /// Off source
    PowerSource mOffSource;

    /// Sink for this switch
    PowerSink mSink;

public:

    Switch(std::wstring imagesDir, int amperage, bool isOn = false);

    /// Destructor
    virtual ~Switch() = default;

    /// Copy constructor/disabled
    Switch(const Switch&) = delete;

    /// Assignment operator/disabled
    void operator=(const Switch&) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    /**
     * Get the source (on or off)
     * @param isOn Is this the on source?
     * @return pointer to source
     */
    PowerSource* GetSource(bool isOn = false) { return isOn ? &mOnSource : &mOffSource; }

    /**
     * Get the sink
     * @return sink pointer
     */
    PowerSink* GetSink() { return &mSink; }

    double Power(double voltage) override;

    /**
     * Get the switch state (on/off)
     * @return bool (true = on, false = off)
     */
    bool GetIsOn() { return mIsOn; }

    void XmlEvent(wxXmlNode* node) override;

    /**
     * Set the position relative to a rack
     * @param x x position
     * @param y y position
     * @param u u in the rack
     * @param xOffset x-offset in the rack
     */
    void SetEquipmentPosition(int x, int y, int u, int xOffset=0) override;

    void SetPowerLocations(bool isLeft = true);

};

#endif //CANADIANEXPERIENCE_SWITCH_H
