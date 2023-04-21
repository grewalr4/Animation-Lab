/**
 * @file WorkingLaboratoryTest.cpp
 * @author Ravi Grewal
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Component.h>
#include <WorkingLaboratory.h>

using namespace std;

/// Sample images directory
const std::wstring ImagesDir = L"test";

TEST(WorkingLaboratoryTest, Construct)
{
    WorkingLaboratory lab(1);
}

TEST(WorkingLaboratoryTest, LaboratoryNumber)
{
    WorkingLaboratory lab(1);
    ASSERT_EQ(lab.GetLaboratoryNumber(), 1);
}

TEST(WorkingLaboratoryTest, AddComponent)
{
    WorkingLaboratory lab(1);
    shared_ptr<Component> c1 = make_shared<Component>(ImagesDir);
    shared_ptr<Component> c2 = make_shared<Component>(ImagesDir);
    shared_ptr<Component> c3 = make_shared<Component>(ImagesDir);
    lab.AddComponent(c1);
    lab.AddComponent(c2);
    lab.AddComponent(c3);
    ASSERT_EQ(c1, lab.GetComponent(0));
    ASSERT_EQ(c2, lab.GetComponent(1));
    ASSERT_EQ(c3, lab.GetComponent(2));
}