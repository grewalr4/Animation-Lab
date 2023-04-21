/**
 * @file MotionSink.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "MotionSink.h"
#include "MotionSource.h"

using namespace std;

/**
 * Construct a motion sink
 * @param component Component this motion sink belongs to
 */
MotionSink::MotionSink(Component* component) : mComponent(component)
{

}

/**
 * Set the source for this motion sink
 * @param source
 */
void MotionSink::SetSource(MotionSource* source)
{
    mSource = source;
}

/**
 * Move the component attached to this sink
 * @param duration Duration to move for
 */
void MotionSink::Move(double duration)
{
    if (mComponent != nullptr)
    {
        mComponent->Move(duration);
    }
}
