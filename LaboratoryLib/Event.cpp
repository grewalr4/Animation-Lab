/**
 * @file Event.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Event.h"

using namespace std;

/**
 * Construct an event
 * @param target of the event
 * @param node for the event
 * @param time of the event
 */
Event::Event(std::wstring target, wxXmlNode* node, double time) : mTarget(target),
    mNode(node), mTime(time)
{

}
