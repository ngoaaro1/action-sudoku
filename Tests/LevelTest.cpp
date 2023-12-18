/**
 * @file LevelTest.cpp
 * @author hankm
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <Level.h>
#include <ids.h>
#include <SudokuGame.h>
using namespace::std;

/**
 * Tests that level is loading in items.
 */
class LevelTest : public ::testing::Test
{
protected:
    /**
     * Test that the level loads 83 object (level 0).
     * @param level The level to test.
     */
    void TestLoad(Level* level)
    {
        ASSERT_EQ(83, (*level->GetItems()).size());

        for (auto item : *level->GetItems())
        {
            ASSERT_FALSE(nullptr == item->GetDeclaration());
        }
    }

};

TEST_F(LevelTest, Construct)
{
    Level level(IDM_LEVEL_LEVEL0);
}

TEST_F(LevelTest, Load)
{
    Level level(IDM_LEVEL_LEVEL0);

    // Make sure the level is loaded in with items attached.
    TestLoad(&level);
}
