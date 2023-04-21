/**
 * @file Laboratory2Factory.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_LABORATORY2FACTORY_H
#define CANADIANEXPERIENCE_LABORATORY2FACTORY_H

class WorkingLaboratory;

/**
 * A factory class to create the lab 2
 */
class Laboratory2Factory {
private:

    /// The resources directory
    std::wstring mResourcesDir;

    /// The images directory
    std::wstring mImagesDir;

public:

    Laboratory2Factory(std::wstring resourcesDir, std::wstring imagesDir);

    std::shared_ptr<WorkingLaboratory> Create();

};

#endif //CANADIANEXPERIENCE_LABORATORY2FACTORY_H
