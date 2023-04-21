/**
 * @file SparkingOrb.h
 * @author Ravi Grewal
 *
 * A sparking orb in the laboratory
 */

#ifndef CANADIANEXPERIENCE_SPARKINGORB_H
#define CANADIANEXPERIENCE_SPARKINGORB_H

#include "Component.h"
#include "PowerSink.h"
#include "Sparky.h"
#include "MotionSink.h"

/**
 * A sparking orb in the laboratory
 */
class SparkingOrb : public Component {
private:

    /// Polygon for orb
    cse335::Polygon mPolygon;

    /// Power sink for this orb
    PowerSink mSink;

    /// Bool to determine sparks
    bool mSpark = false;

    /// Sparky object used to render sparks between orbs
    cse335::Sparky mSparky;

    /// Motion sink for this orb
    MotionSink mMotionSink;

    /// Motion duration
    double mDuration = 0;

    /// Motion distance
    double mDistance = 0;

public:

    SparkingOrb(std::wstring imagesDir);

    /// Destructor
    virtual ~SparkingOrb() = default;

    /// Copy constructor/disabled
    SparkingOrb(const SparkingOrb&) = delete;

    /// Assignment operator/disabled
    void operator=(const SparkingOrb&) = delete;

    /**
     * Get the power sink for this orb
     * @return pointer to sink
     */
    PowerSink* GetSink() { return &mSink; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    double Power(double voltage) override;

    void Update(double time) override;

    void Move(double duration) override;

    /**
     * Get the motion sink
     * @return
     */
    MotionSink* GetMotionSink() { return &mMotionSink; }
};

#endif //CANADIANEXPERIENCE_SPARKINGORB_H
