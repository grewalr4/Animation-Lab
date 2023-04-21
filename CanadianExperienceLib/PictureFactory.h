/**
 * @file PictureFactory.h
 * @author Ravi Grewal
 *
 * A factory class that builds our picture.
 */

#ifndef CANADIANEXPERIENCE_PICTUREFACTORY_H
#define CANADIANEXPERIENCE_PICTUREFACTORY_H

class Picture;

/**
 * A factory class that builds our picture.
 */
class PictureFactory {
public:
    std::shared_ptr<Picture> Create(std::wstring resourcesDir);

};

#endif //CANADIANEXPERIENCE_PICTUREFACTORY_H
