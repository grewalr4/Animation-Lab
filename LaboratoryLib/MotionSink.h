/**
 * @file MotionSink.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MOTIONSINK_H
#define CANADIANEXPERIENCE_MOTIONSINK_H

#include "Component.h"

class MotionSource;

/**
 * A motion sink has motion rendered to it
 */
class MotionSink {
private:

    /// Source connected to this sink
    MotionSource* mSource = nullptr;

    /// The component this sink is owned by
    Component* mComponent = nullptr;
    
public:

    MotionSink(Component* component);

    /// Destructor
    virtual ~MotionSink() = default;

    /// Copy constructor/disabled
    MotionSink(const MotionSink&) = delete;

    /// Assignment operator/disabled
    void operator=(const MotionSink&) = delete;

    void Move(double duration);

    /**
     * Get the source
     * @return
     */
    MotionSource* GetSource() { return mSource; }

    /**
     * Set the component this Motion sink is owned by
     * @param component
     */
    void SetComponent(Component* component) { mComponent = component; }

    /**
     * Get the component this Motion sink is owned by
     * @return
     */
    Component* GetComponent() { return mComponent; }

    void SetSource(MotionSource* source);

};

#endif //CANADIANEXPERIENCE_MOTIONSINK_H
