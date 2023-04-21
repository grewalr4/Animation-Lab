/**
 * @file Laboratory1Factory.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_LABORATORY1FACTORY_H
#define CANADIANEXPERIENCE_LABORATORY1FACTORY_H

class WorkingLaboratory;

/**
 * A factor class to create the lab 1
 */
class Laboratory1Factory {
private:

    /// The resources directory
    std::wstring mResourcesDir;

    /// The images directory
    std::wstring mImagesDir;

public:

    Laboratory1Factory(std::wstring resourcesDir, std::wstring imagesDir);

    std::shared_ptr<WorkingLaboratory> Create();
};

#endif //CANADIANEXPERIENCE_LABORATORY1FACTORY_H
