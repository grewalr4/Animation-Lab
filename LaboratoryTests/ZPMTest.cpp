/**
 * @file ZPMTest.cpp
 * @author Ravi Grewal
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <ZPM.h>

using namespace std;

/// Sample images directory
const std::wstring ImagesDir = L"test";

TEST(ZPMTest, Construct)
{
    ZPM zpm(ImagesDir);
}

TEST(ZPMTest, Voltage)
{
    ZPM zpm(ImagesDir);
    ASSERT_NEAR(zpm.GetVoltage(), 1000.00, 0.0001);
    ASSERT_NEAR(zpm.GetCurrent(), 0, 0.0001);
}