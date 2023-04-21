/**
 * @file Cable.cpp
 * @author Ravi Grewal
 */

#include "pch.h"
#include "Cable.h"

using namespace std;

/// Smallest possible cable size
const int CableMinimumWidth = 3;

/// The width of the cable line is CableMinimumWidth
/// plus capacity / CableCapacityDivisor
const int CableCapacityDivisor = 200;

/// Cable red
const int CableRed = 40;

/// Cable green
const int CableGreen = 40;

/// Cable blue
const int CableBlue = 40;

/**
 * Construct a cable
 * @param imagesDir Images directory for image loading
 * @param current Current for the cable
 */
Cable::Cable(std::wstring imagesDir, double current) : Component(imagesDir),
    mSource(imagesDir, this), mSink(imagesDir, this)
{
    mSource.SetCurrent(current);
}

/**
 * Add a clamp
 * @param x x-coord for clamp
 * @param y y-coord for clamp
 * @param rotation rotation for clamp
 * @param speed speed for clamp
 */
void Cable::AddClamp(int x, int y, double rotation, double speed)
{
    mClamps.push_back(make_shared<Clamp>(wxPoint(x, y), rotation, speed));
}

/**
 * Draw the component at the currently specified location
 * @param graphics Graphics object to render to
 * @param x X location
 * @param y Y location
 */
void Cable::Draw(std::shared_ptr<wxGraphicsContext> graphics, int x, int y)
{
    // sink point -> first clamp
    // first clamp -> second clamp
    // ...
    // x clamp -> source point
    auto pos1x = mSink.GetPosition().x + x + mSink.GetSource()->GetComponent()->GetPosition().x;
    auto pos1y = mSink.GetPosition().y + y + mSink.GetSource()->GetComponent()->GetPosition().y;
    wxPoint pos1 = {pos1x, pos1y};
    auto pos2x = mSource.GetPosition().x + x + mSource.GetSink()->GetComponent()->GetPosition().x;
    auto pos2y = mSource.GetPosition().y + y + mSource.GetSink()->GetComponent()->GetPosition().y;
    wxPoint pos2 = {pos2x, pos2y};

    //
    // Compute the endpoint positions for the source and sink
    //
    Endpoint e1(pos1, mSink.GetRotation(), mSink.GetSpeed());
    Endpoint e2(pos2, mSource.GetRotation(), mSource.GetSpeed());

    DrawBezierCurve(graphics, x, y,&e1, &e2);
//    else
//    {
//        if (mClamps.size() > 0)
//        {
//            DrawBezierCurve(graphics, x, y, &e1, mClamps[0].get());
//        }
//        for (int i = 0; i < mClamps.size() - 1; ++i)
//        {
//            DrawBezierCurve(graphics, x, y, mClamps[i].get(), mClamps[i+1].get());
//        }
//        DrawBezierCurve(graphics, x, y, mClamps[mClamps.size()-1].get(), &e2);
//    }

}

/**
 * Draw a Bezier Curve between Endpoints e1 and e4
 * @param graphics Graphics to render to
 * @param x X-offset
 * @param y Y-offset
 * @param e1 Endpoint A
 * @param e4 Endpoint B
 */
void Cable::DrawBezierCurve(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, Endpoint* e1, Endpoint* e4)
{
    //
    // Calculate values for drawing
    //
    double rotation1 = e1->GetRotation();
    double speed1 = e1->GetSpeed();
    double rotation2 = e4->GetRotation();
    double speed2 = e4->GetSpeed();
    int width = int(CableMinimumWidth + mSource.GetCurrent() / CableCapacityDivisor);

    //
    // Prepare to draw by setting pen, color, etc.
    //
    wxPen pen;  // pen to draw the curve
    pen.SetCap(wxCAP_BUTT);
    pen.SetColour(wxColour(CableRed, CableGreen, CableBlue));
    pen.SetWidth(width);
    graphics->SetPen(pen);

    //
    // Path computations
    //
    auto path = graphics->CreatePath();
    auto p1x = e1->GetPosition().x;
    auto p1y = e1->GetPosition().y;
    auto p4x = e4->GetPosition().x;
    auto p4y = e4->GetPosition().y;

    auto p2x = p1x + sin(rotation1 * M_PI * 2) * speed1;
    auto p2y = p1y - cos(rotation1 * M_PI * 2) * speed1;
    auto p3x = p2x - sin(rotation2 * M_PI * 2) * speed2;
    auto p3y = p2y + cos(rotation2 * M_PI * 2) * speed2;

    path.MoveToPoint(p1x, p1y);
    path.AddCurveToPoint(p2x, p2y, p3x, p3y, p4x, p4y);
    graphics->StrokePath(path);
}

double Cable::Power(double voltage)
{
    return mSource.Power(voltage);
}

void Cable::SetPositions()
{
    mSink.SetPosition(mSink.GetSource()->GetPosition());
    mSource.SetPosition(mSource.GetSink()->GetPosition());
}
