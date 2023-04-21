/**
 * @file Shape.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_SHAPE_H
#define CANADIANEXPERIENCE_SHAPE_H

#include "Component.h"

/**
 * A shape component in the laboratory (e.g. blank panels)
 */
class Shape : public Component {
private:

    /// The polygon for this shape (defaults to back item)
    cse335::Polygon mPolygon;

public:

    /**
     * Construct a shape
     * @param imagesDir Images directory
     */
    Shape(std::wstring imagesDir) : Component(imagesDir) {}

    /// Destructor
    virtual ~Shape() = default;

    /// Copy constructor/disabled
    Shape(const Shape&) = delete;

    /// Assignment operator/disabled
    void operator=(const Shape&) = delete;

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    /**
     * Set the image
     * @param filename
     */
    void SetImage(std::wstring filename) { mPolygon.SetImage(GetImagesDir() + filename); }

    /**
     * Create a rectangle.
     *
     * If the height parameter is not supplied and an image
     * has been set, the height will be computed so as to
     * keep the original image aspect ratio correct.
     *
     * @param x Left side X
     * @param y Bottom left Y
     * @param width Width of the rectangle
     * @param height Height of the rectangle
     */
    void Rectangle(int x, int y, int width = 0, int height = 0) { mPolygon.Rectangle(x, y, width, height); }
    
};

#endif //CANADIANEXPERIENCE_SHAPE_H
