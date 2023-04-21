/**
 * @file Endpoint.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Endpoint.h"

using namespace std;

/**
 * Construct an endpoint
 * @param position
 * @param rotation
 * @param speed
 */
Endpoint::Endpoint(wxPoint position, double rotation, double speed) :
    mPosition(position), mRotation(rotation), mSpeed(speed)
{

}
