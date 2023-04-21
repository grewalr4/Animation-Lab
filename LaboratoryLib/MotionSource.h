/**
 * @file MotionSource.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MOTIONSOURCE_H
#define CANADIANEXPERIENCE_MOTIONSOURCE_H

#include "Component.h"

class MotionSink;

/**
 * A motion source renders motion in its sink
 */
class MotionSource {
private:

    /// Sink connected to this source
    MotionSink* mSink = nullptr;

    /// The component this sink is owned by
    Component* mComponent = nullptr;

public:

    MotionSource(Component* component);

    /// Destructor
    virtual ~MotionSource() = default;

    /// Copy constructor/disabled
    MotionSource(const MotionSource&) = delete;

    /// Assignment operator/disabled
    void operator=(const MotionSource&) = delete;

    void Move(double duration);

    /**
     * Get the sink
     * @return
     */
    MotionSink* GetSink() { return mSink; }

    /**
     * Set the component this Motion sink is owned by
     * @param component
     */
    void SetComponent(Component* component) { mComponent = component; }

    /**
     * Get the component this Motion source is owned by
     * @return
     */
    Component* GetComponent() { return mComponent; }

    void SetSink(MotionSink* sink);

};

#endif //CANADIANEXPERIENCE_MOTIONSOURCE_H
