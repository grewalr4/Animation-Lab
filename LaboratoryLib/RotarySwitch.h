/**
 * @file RotarySwitch.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ROTARYSWITCH_H
#define CANADIANEXPERIENCE_ROTARYSWITCH_H

#include "Component.h"
#include "PowerSink.h"
#include "PowerSource.h"
#include "Polygon.h"
#include "Equipment.h"

/**
 * A switch with many outputs
 */
class RotarySwitch : public Component, public Equipment {
private:

    /// Power sink
    PowerSink mSink;

    /// Power sources
    std::vector<std::shared_ptr<PowerSource>> mSources;

    /// Current source number (default is 0)
    int mSourceNum = 0;

    /// Panel polygon
    cse335::Polygon mPanel;

    /// Rail polygon
    cse335::Polygon mRail;

    /// Switch background polygon
    cse335::Polygon mSwitch;

    /// Knob polygon
    cse335::Polygon mKnob;

public:

    RotarySwitch(std::wstring imagesDir, int sourceNum);

    /// Destructor
    virtual ~RotarySwitch() = default;

    /// Copy constructor/disabled
    RotarySwitch(const RotarySwitch&) = delete;

    /// Assignment operator/disabled
    void operator=(const RotarySwitch&) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    double Power(double voltage) override;

    void SetEquipmentPosition(int x, int y, int u, int xOffset) override;

    /**
     * Get a source at sourceNum position
     * @param sourceNum Position of source to get
     * @return pointer to source
     */
    PowerSource* GetSource(int sourceNum) { return mSources[sourceNum].get(); }

    /**
     * Get the power sink for this rotary switch
     * @return pointer to power sink
     */
    PowerSink* GetSink() { return &mSink; }

    void XmlEvent(wxXmlNode* node) override;
};

#endif //CANADIANEXPERIENCE_ROTARYSWITCH_H
