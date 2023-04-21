/**
 * @file AnimChannelAngleTest.cpp
 * @author Ravi Grewal
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <AnimChannelAngle.h>

TEST(AnimChannelAngleTest, Name)
{
    AnimChannelAngle channel;
    channel.SetName(L"abcdexx");
    ASSERT_EQ(std::wstring(L"abcdexx"), channel.GetName());
}