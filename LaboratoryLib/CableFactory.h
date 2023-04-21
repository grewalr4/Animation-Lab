/**
 * @file CableFactory.h
 * @author Ravi Grewal
 * @author Ravi Grewal
 *
 * A simple factory to make it easier to create cables
 */

#ifndef CANADIANEXPERIENCE_CABLEFACTORY_H
#define CANADIANEXPERIENCE_CABLEFACTORY_H

#include "Cable.h"

class WorkingLaboratory;

/**
 *  A simple factory to make it easier to create cables
 */
class CableFactory
{
private:
    /// The laboratory we are adding the cable to
    std::shared_ptr<WorkingLaboratory> mLaboratory;

    /// Directory containing the images
    std::wstring mImagesDir;

public:
    CableFactory(std::shared_ptr<WorkingLaboratory> laboratory, std::wstring imagesDir);

    std::shared_ptr<Cable> Create(PowerSource *source, PowerSink *sink, double sourceSpeed = 0, double sinkSpeed = 0);
};

#endif //CANADIANEXPERIENCE_CABLEFACTORY_H
