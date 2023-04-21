/**
 * @file PowerSource.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_POWERSOURCE_H
#define CANADIANEXPERIENCE_POWERSOURCE_H

#include "Component.h"
#include "Endpoint.h"

class PowerSink;

/**
 * Power source capabilities are contained here
 */
class PowerSource : public Endpoint {
private:

    /// Sink connected to this source
    PowerSink* mSink = nullptr;

    /// The component this sink is owned by
    Component* mComponent = nullptr;

    /// The polygon for this connection
    cse335::Polygon mPolygon;

    /// The current for this source
    double mCurrent = 0;

    /// The size of this source
    int mSize = 0;

public:

    PowerSource(std::wstring imagesDir, Component* component, double current=0);
    
    /// Destructor
    virtual ~PowerSource() = default;

    /// Copy constructor/disabled
    PowerSource(const PowerSource&) = delete;

    /// Assignment operator/disabled
    void operator=(const PowerSource&) = delete;

    double Power(double voltage);

    /**
     * Get the sink
     * @return pointer to sink
     */
    PowerSink* GetSink() { return mSink; }

    /**
     * Set the component this power sink is owned by
     * @param component
     */
    void SetComponent(Component* component) { mComponent = component; }

    /**
     * Get the component this power source is owned by
     * @return pointer to component
     */
    Component* GetComponent() { return mComponent; }

    void SetSink(PowerSink* sink);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y);

    /**
     * Get the current for this source
     * @return current as double
     */
    double GetCurrent() { return mCurrent; }

    /**
     * Set the current for this source
     * @param current New current
     */
    void SetCurrent(double current) { mCurrent = current; }
};

#endif //CANADIANEXPERIENCE_POWERSOURCE_H
