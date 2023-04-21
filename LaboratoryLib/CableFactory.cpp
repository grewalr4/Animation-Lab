/**
 * @file CableFactory.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "CableFactory.h"
#include "WorkingLaboratory.h"

using namespace std;

/**
 * Construct a cable factory
 * @param laboratory Laboratory this factory is connected to
 * @param imagesDir Images directory
 */
CableFactory::CableFactory(std::shared_ptr<WorkingLaboratory> laboratory, std::wstring imagesDir) :
        mLaboratory(laboratory), mImagesDir(imagesDir)
{

}

/**
 * Create cable with the current parameterization
 * @param source Air source we are connecting from
 * @param sink Air sink we are connecting to
 * @param sourceSpeed Optional speed for the source connection
 * @param sinkSpeed Optional speed for the sink connection
 * @return Tubing object
*/
std::shared_ptr<Cable> CableFactory::Create(PowerSource* source, PowerSink* sink, double sourceSpeed, double sinkSpeed)
{
    auto cable = std::make_shared<Cable>(mImagesDir, source->GetCurrent());
    source->SetSink(cable->GetSink());
    cable->GetSource()->SetSink(sink);
    cable->SetPositions();

    if (sourceSpeed > 0)
    {
        source->SetSpeed(sourceSpeed);
    }

    if (sinkSpeed > 0)
    {
        sink->SetSpeed(sinkSpeed);
    }

    mLaboratory->AddComponent(cable);
    return cable;
}

