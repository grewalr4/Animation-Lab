/**
 * @file HaroldFactory.h
 * @author Ravi Grewal
 *
 * Factory class that builds the Harold character
 */

#ifndef CANADIANEXPERIENCE_HAROLDFACTORY_H
#define CANADIANEXPERIENCE_HAROLDFACTORY_H

class Actor;

/**
 * Factory class that builds the Harold character
 */
class HaroldFactory {
public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};

#endif //CANADIANEXPERIENCE_HAROLDFACTORY_H
