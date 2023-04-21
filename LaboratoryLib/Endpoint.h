/**
 * @file Endpoint.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ENDPOINT_H
#define CANADIANEXPERIENCE_ENDPOINT_H

/**
 * An endpoint for drawing cables
 */
class Endpoint {
private:

    /// Position
    wxPoint mPosition = {0, 0};

    /// Rotation
    double mRotation = 0;

    /// Speed
    double mSpeed = 0;

public:

    Endpoint() {}

    Endpoint(wxPoint position, double rotation, double speed);

    /// Destructor
    virtual ~Endpoint() = default;

    /// Copy constructor/disabled
    Endpoint(const Endpoint&) = delete;

    /// Assignment operator/disabled
    void operator=(const Endpoint&) = delete;

    /**
     * Get the position of this endpoint
     * @return wxPoint position
     */
    wxPoint GetPosition() { return mPosition; }

    /**
     * Set the position of this endpoint
     * @param position New position
     */
    void SetPosition(wxPoint position) { mPosition = position; }

    /**
     * Get the rotation
     * @return double rotation
     */
    double GetRotation() { return mRotation; }

    /**
     * Set the rotation
     * @param rotation New rotation
     */
    void SetRotation(double rotation) { mRotation = rotation; }

    /**
     * Get the speed
     * @return double speed
     */
    double GetSpeed() { return mSpeed; }

    /**
     * Set the speed
     * @param speed New speed
     */
    void SetSpeed(double speed) { mSpeed = speed; }

};

#endif //CANADIANEXPERIENCE_ENDPOINT_H
