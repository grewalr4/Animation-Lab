/**
 * @file Event.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_EVENT_H
#define CANADIANEXPERIENCE_EVENT_H

#include <wx/xml/xml.h>

/**
 * Encapsulates an animation event rendered by an XML node
 */
class Event {
private:

    /// The target name
    std::wstring mTarget;

    /// The node associated with this event
    wxXmlNode* mNode = nullptr;
    
    /// The time for this event
    double mTime = 0;

public:

    /// Destructor
    virtual ~Event() = default;

    /// Copy constructor/disabled
    Event(const Event&) = delete;

    /// Assignment operator/disabled
    void operator=(const Event&) = delete;
    
    Event(std::wstring target, wxXmlNode* node, double time);

    /**
     * Get the time
     * @return
     */
    double GetTime() { return mTime; }

    /**
     * Get the node
     * @return
     */
    wxXmlNode* GetNode() { return mNode; }

    /**
     * Get the target name
     * @return
     */
    std::wstring GetTarget() { return mTarget; }

};

#endif //CANADIANEXPERIENCE_EVENT_H
