/**
 * @file DistributionPanel.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_DISTRIBUTIONPANEL_H
#define CANADIANEXPERIENCE_DISTRIBUTIONPANEL_H

#include "Component.h"
#include "Equipment.h"
#include "PowerSink.h"
#include "PowerSource.h"

/**
 * A distribution panel moves power to many different components
 */
class DistributionPanel : public Component, public Equipment {
private:

    /// The polygon for this distribution panel
    cse335::Polygon mPolygon;

    /// The sources
    std::vector<std::shared_ptr<PowerSource>> mSources;

    /// The sink
    PowerSink mSink;

public:

    DistributionPanel(std::wstring imagesDir, double voltage);

    /// Destructor
    virtual ~DistributionPanel() = default;

    /// Copy constructor/disabled
    DistributionPanel(const DistributionPanel&) = delete;

    /// Assignment operator/disabled
    void operator=(const DistributionPanel&) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    /**
     * Set the position relative to a rack
     * @param x x position
     * @param y y position
     * @param u u in the rack
     * @param xOffset x-offset in the rack
     */
    void SetEquipmentPosition(int x, int y, int u, int xOffset=0) override;

    /**
     * Get the source at source #
     * @param source Source #
     * @return source # in sources
     */
    PowerSource* GetSource(int source) { return mSources[source-1].get(); }

    /**
     * Get the sink
     * @return sink
     */
    PowerSink* GetSink() { return &mSink; }

    void AddSource(double current);

    double Power(double voltage) override;
};

#endif //CANADIANEXPERIENCE_DISTRIBUTIONPANEL_H
