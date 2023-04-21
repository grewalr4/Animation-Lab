/**
 * @file Rheostat.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_RHEOSTAT_H
#define CANADIANEXPERIENCE_RHEOSTAT_H

#include "Component.h"
#include "PowerSink.h"
#include "PowerSource.h"

/**
 * Varies the voltage passing through
 */
class Rheostat : public Component {
private:

    /// Background polygon
    cse335::Polygon mBackground;

    /// Wheel polygon
    cse335::Polygon mKnob;

    /// Power source for this rheostat
    PowerSource mSource;

    /// Power sink for this rheostat
    PowerSink mSink;

    /// Motion duration
    double mDuration = 0;

    /// Motion rotation
    double mRotationAngle = 0;

    /// Motion rotation rate
    double mRotationRate = 0;

    /// Currently moving?
    bool mMoving = false;

    /// Current rotation
    double mCurrentRotation = 0;

public:

    Rheostat(std::wstring imagesDir);

    /// Destructor
    virtual ~Rheostat() = default;

    /// Copy constructor/disabled
    Rheostat(const Rheostat&) = delete;

    /// Assignment operator/disabled
    void operator=(const Rheostat&) = delete;

    void XmlEvent(wxXmlNode* node) override;

    void Update(double time) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    double Power(double voltage) override;

    /**
     * Get the power source for this rheostat
     * @return pointer to power source
     */
    PowerSource* GetSource() { return &mSource; }

    /**
     * Get the power sink for this rheostat
     * @return pointer to power sink
     */
    PowerSink* GetSink() { return &mSink; }
};

#endif //CANADIANEXPERIENCE_RHEOSTAT_H
