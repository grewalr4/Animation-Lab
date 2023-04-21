/**
 * @file Light.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_LIGHT_H
#define CANADIANEXPERIENCE_LIGHT_H

#include "Component.h"
#include "Polygon.h"
#include "PowerSink.h"

/**
 * A light in the laboratory
 */
class Light : public Component {
private:

    /// The background polygon
    cse335::Polygon mBackgroundPolygon;

    /// The light polygon
    cse335::Polygon mLightPolygon;

    /// Power on?
    bool mIsOn = false;

    /// The power sink
    PowerSink mSink;

public:

    Light(std::wstring imagesDir, std::wstring backgroundImage, std::wstring lightImage, int width);

    /// Destructor
    virtual ~Light() = default;

    /// Copy constructor/disabled
    Light(const Light&) = delete;

    /// Assignment operator/disabled
    void operator=(const Light&) = delete;

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);

    /**
     * Get a pointer to the power sink
     * @return pointer to power sink
     */
    PowerSink *GetSink() {return &mSink;}

    double Power(double voltage) override;

};

#endif //CANADIANEXPERIENCE_LIGHT_H
