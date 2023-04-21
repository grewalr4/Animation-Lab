/**
 * @file SpartyFactory.h
 * @author Ravi Grewal
 *
 * Factory class to create Sparty.
 */

#ifndef CANADIANEXPERIENCE_SPARTYFACTORY_H
#define CANADIANEXPERIENCE_SPARTYFACTORY_H

class Actor;

/**
 * Factory class to create Sparty.
 */
class SpartyFactory {
private:

public:

    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};

#endif //CANADIANEXPERIENCE_SPARTYFACTORY_H
