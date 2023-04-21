/**
 * @file SwitchTest.cpp
 * @author Ravi Grewal
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Switch.h>

using namespace std;

/// Sample images directory
const std::wstring ImagesDir = L"test";

TEST(SwitchTest, Construct)
{
    auto switch1 = make_shared<Switch>(ImagesDir, 100, true);
}

TEST(SwitchTest, GetterSetter)
{
    auto switch1 = make_shared<Switch>(ImagesDir, 100, true);
    ASSERT_TRUE(switch1->GetIsOn());

    auto switch2 = make_shared<Switch>(ImagesDir, 100);
    ASSERT_FALSE(switch2->GetIsOn());
}