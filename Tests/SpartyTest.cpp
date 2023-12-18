/**
 * @file SpartyTest.cpp
 * @author hankm
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Level.h>
#include <Sparty.h>
#include <ids.h>
#include <Digit.h>
#include <Declaration.h>
#include <NumberDeclaration.h>
#include <ids.h>
#include <Xray.h>
#include <memory>
#include <DeclarationVisitor.h>
#include <GetDeclarationVisitor.h>
#include <cmath>

using namespace std;

class SpartyMock : public Sparty
{
public:
    SpartyMock(Level* level) : Sparty(level) {}


};
class SpartyTest : public ::testing::Test
{
public:
    void TestLocation(SpartyMock* sparty)
    {
        ASSERT_EQ(1,sparty->GetCol());
        ASSERT_EQ(1,sparty->GetRow());
        ASSERT_FALSE(sparty->GetCol() == 30);
        ASSERT_FALSE(sparty->GetRow() == 2);
        ASSERT_FALSE(sparty->GetCol() == 90);
        ASSERT_FALSE(sparty->GetRow() == 110);
    }
    void TestSpeed(SpartyMock* sparty)
    {
        ASSERT_EQ(25,sparty->GetSpeedX());
        ASSERT_EQ(25,sparty->GetSpeedY());
        ASSERT_FALSE(sparty->GetSpeedX() == 30);
        ASSERT_FALSE(sparty->GetSpeedY() == 60);
    }
};

TEST_F(SpartyTest, Location)
{
    Level level(IDM_LEVEL_LEVEL1);
    SpartyMock sparty(&level);
    sparty.SetLocation(1,1);
    TestLocation(&sparty);
    sparty.ChangeSpeed(25,25);
    TestSpeed(&sparty);



}

TEST(SpartyTest, Regurgitate)
{
    Level level(IDM_LEVEL_LEVEL2);
    
}