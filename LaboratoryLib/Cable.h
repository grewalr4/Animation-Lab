/**
 * @file Cable.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CABLE_H
#define CANADIANEXPERIENCE_CABLE_H

#include "Component.h"
#include "PowerSource.h"
#include "PowerSink.h"
#include "Endpoint.h"

/**
 * A cable in the laboratory to distribute power
 */
class Cable : public Component {
private:

    /// Source for the cable
    PowerSource mSource;
    
    /// Sink for the cable
    PowerSink mSink;

protected:

    /**
     * A clamp for drawing the cable
     */
    class Clamp : public Endpoint {
    private:

    public:

        /**
         * Construct a clamp
         * @param position
         * @param rotation
         * @param speed
         */
        Clamp(wxPoint position, double rotation, double speed) : Endpoint(position, rotation, speed) {}

        /// Destructor
        virtual ~Clamp() = default;

        /// Copy constructor/disabled
        Clamp(const Clamp&) = delete;

        /// Assignment operator/disabled
        void operator=(const Clamp&) = delete;

    };

private:

    /// The clamps for this cable
    std::vector<std::shared_ptr<Clamp>> mClamps;

public:

    Cable(std::wstring imagesDir, double current);

    /// Destructor
    virtual ~Cable() = default;

    /// Copy constructor/disabled
    Cable(const Cable&) = delete;

    /// Assignment operator/disabled
    void operator=(const Cable&) = delete;

    /**
     * Get the source object for this Cable
     * @return PowerSource object
     */
    PowerSource* GetSource() { return &mSource; }

    /**
     * Get the sink for this cable
     * @return pointer to sink
     */
    PowerSink* GetSink() { return &mSink; }

    void AddClamp(int x, int y, double rotation, double speed);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    void DrawBezierCurve(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, Endpoint* e1, Endpoint* e4);

    /**
     * Facilitate the movement of power
     * @param voltage Voltage to pass
     * @return current
     */
    double Power(double voltage) override;

    /**
     * Set the positions of the source and sink
     * to prepare for drawing
     */
    void SetPositions();
};

#endif //CANADIANEXPERIENCE_CABLE_H
