/**
 * @file PowerSink.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_POWERSINK_H
#define CANADIANEXPERIENCE_POWERSINK_H

#include "Component.h"
#include "Endpoint.h"

class PowerSource;

/**
 * Power sink capabilities are contained here
 */
class PowerSink : public Endpoint {
private:

    /// Source connected to this sink
    PowerSource* mSource = nullptr;

    /// The component this sink is owned by
    Component* mComponent = nullptr;

    /// The polygon for this connection
    cse335::Polygon mPolygon;

    /// The size of this connection
    int mSize = 0;

public:

    PowerSink(std::wstring imagesDir, Component* component);
    
    /// Destructor
    virtual ~PowerSink() = default;

    /// Copy constructor/disabled
    PowerSink(const PowerSink&) = delete;

    /// Assignment operator/disabled
    void operator=(const PowerSink&) = delete;

    double Power(double voltage);

    /**
     * Get the source
     * @return
     */
    PowerSource* GetSource() { return mSource; }

    /**
     * Set the component this power sink is owned by
     * @param component
     */
    void SetComponent(Component* component) { mComponent = component; }

    /**
     * Get the component this power sink is owned by
     * @return
     */
    Component* GetComponent() { return mComponent; }

    void SetSource(PowerSource* source);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);
};

#endif //CANADIANEXPERIENCE_POWERSINK_H
