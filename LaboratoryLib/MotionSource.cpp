/**
 * @file MotionSource.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "MotionSource.h"
#include "MotionSink.h"

using namespace std;

/**
 * Construct a motion source
 * @param component Component that this motion source belongs to
 */
MotionSource::MotionSource(Component* component) : mComponent(component)
{

}

/**
 * Set the sink for this motion source
 * @param sink
 */
void MotionSource::SetSink(MotionSink* sink)
{
    mSink = sink;
    sink->SetSource(this);
}

/**
 * Facilitate movement of a motion sink
 * @param duration Duration to move for
 */
void MotionSource::Move(double duration)
{
    if (mSink != nullptr)
    {
        mSink->Move(duration);
    }
}


