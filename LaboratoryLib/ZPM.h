/**
 * @file ZPM.h
 * @author Ravi Grewal
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ZPM_H
#define CANADIANEXPERIENCE_ZPM_H

#include "Component.h"
#include "Polygon.h"
#include "PowerSource.h"

/**
 * The Zero-point module for the laboratory
 */
class ZPM : public Component {
private:

    /// The polygon for the ZPM
    cse335::Polygon mPolygon;

    /// The power source for this ZPM
    PowerSource mSource;

public:

    ZPM(std::wstring imagesDir);

    /// Destructor
    virtual ~ZPM() = default;

    /// Copy constructor/disabled
    ZPM(const ZPM&) = delete;

    /// Assignment operator/disabled
    void operator=(const ZPM&) = delete;

    /**
     * Set the image
     * @param filename
     */
    void SetImage(std::wstring filename) { mPolygon.SetImage(GetImagesDir() + filename); }

    /**
     * Create a rectangle where 0,0 is the bottom center of the rectangle.
     *
     * Must set an image first if not providing a width and height.
     *
     * @param width Width of the rectangle in pixels. If not supplied, use the image width.
     * @param height Height of the rectangle in pixels. If not supplied, select a height such
     * that the aspect ratio matches that of the image.
     */
    void BottomCenteredRectangle(int width = 0, int height = 0) { mPolygon.BottomCenteredRectangle(width, height); }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y) override;

    /**
     * Get the source object for this component
     * @return PowerSource object
     */
    PowerSource* GetSource() { return &mSource; }

    void Update(double time);

    double Power(double voltage) override;
};

#endif //CANADIANEXPERIENCE_ZPM_H
