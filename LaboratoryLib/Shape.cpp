/**
 * @file Shape.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Shape.h"

using namespace std;

/**
 * Draw the component at the currently specified location
 * @param graphics Graphics object to render to
 * @param x X location
 * @param y Y location
 */
void Shape::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    mPolygon.DrawPolygon(graphics, x + GetPosition().x, y + GetPosition().y);
}
