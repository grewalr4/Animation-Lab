/**
 * @file Winch.h
 * @author Ravi Grewal
 *
 * A winch is a motion source in the laboratory
 */

#ifndef CANADIANEXPERIENCE_WINCH_H
#define CANADIANEXPERIENCE_WINCH_H

#include "Component.h"
#include "Equipment.h"
#include "MotionSource.h"

/**
 * A winch in the laboratory to move motion sinks
 */
class Winch : public Component, public Equipment {
private:

    /// Background polygon
    cse335::Polygon mBackground;

    /// Wheel polygon
    cse335::Polygon mWheel;

    /// Motion source for this winch
    MotionSource mMotionSource;

    /// Motion duration
    double mDuration = 0;

    /// Motion rotation
    double mRotationAngle = 0;

    /// Motion rotation rate
    double mRotationRate = 0;

    /// Currently moving?
    bool mMoving = false;

public:

    Winch(std::wstring imagesDir);

    /// Destructor
    virtual ~Winch() = default;

    /// Copy constructor/disabled
    Winch(const Winch&) = delete;

    /// Assignment operator/disabled
    void operator=(const Winch&) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    void SetEquipmentPosition(int x, int y, int u, int xOffset=0);

    void Move(double duration) override;

    void XmlEvent(wxXmlNode* node);

    void Update(double time) override;

    /**
     * Get the motion source for the winch
     * @return pointer to motion source
     */
    MotionSource* GetMotionSource() { return &mMotionSource; }
};

#endif //CANADIANEXPERIENCE_WINCH_H
