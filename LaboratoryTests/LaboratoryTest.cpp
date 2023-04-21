/**
 * @file LaboratoryTest.cpp
 * @author Ravi Grewal
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <LaboratoryFactory.h>
#include <Laboratory.h>

TEST(LaboratoryTest, Constructor)
{
    LaboratoryFactory factory(L".");
    auto laboratory = factory.CreateLaboratory();

    ASSERT_NE(nullptr, laboratory);
}

TEST(LaboratoryTest, Location)
{
    LaboratoryFactory factory(L".");
    auto laboratory = factory.CreateLaboratory();

    laboratory->SetLocation(wxPoint(123, 456));
    auto position = laboratory->GetLocation();
    ASSERT_EQ(123, position.x);
    ASSERT_EQ(456, position.y);
}

TEST(LaboratoryTest, LaboratoryTime)
{
    LaboratoryFactory factory(L".");
    auto laboratory = factory.CreateLaboratory();

    laboratory->SetFrameRate(30);
    laboratory->SetLaboratoryFrame(123);

    ASSERT_NEAR(123.0 / 30.0, laboratory->GetLaboratoryTime(), 0.001);

    // Different frame rate
    laboratory->SetFrameRate(15);
    laboratory->SetLaboratoryFrame(201);
    ASSERT_NEAR(201.0 / 15.0, laboratory->GetLaboratoryTime(), 0.001);
}


TEST(LaboratoryTest, LaboratoryNumber)
{
    LaboratoryFactory factory(L".");
    auto laboratory = factory.CreateLaboratory();

    // Try laboratory number 1
    laboratory->SetLaboratoryNumber(1);
    ASSERT_EQ(1, laboratory->GetLaboratoryNumber());

    // Try laboratory number 2
    laboratory->SetLaboratoryNumber(2);
    ASSERT_EQ(2, laboratory->GetLaboratoryNumber());

    // Ensure we can go back to laboratory number 1
    laboratory->SetLaboratoryNumber(1);
    ASSERT_EQ(1, laboratory->GetLaboratoryNumber());
}