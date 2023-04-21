/**
 * @file ComponentTest.cpp
 * @author Ravi Grewal
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Component.h>
#include <WorkingLaboratory.h>

using namespace std;

/// Sample images directory
const std::wstring ImagesDir = L"test";

TEST(ComponentTest, Construct)
{
    Component c1(ImagesDir);
}

TEST(ComponentTest, GetLaboratory)
{
    WorkingLaboratory lab(1);
    Component c1(ImagesDir);
    c1.SetLaboratory(&lab);
    ASSERT_EQ(&lab, c1.GetLaboratory());
}