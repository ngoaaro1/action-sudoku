/**
 * @file SudokuBoardTest.cpp
 * @author hankm
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <SudokuBoard.h>
#include <ids.h>
#include <Level.h>

/// Test solution string constant.
const std::wstring TestStrSolution = L"5 2 6 7 0 3 4 1 8 3 4 0 2 8 1 5 7 6 8 1 7 5 4 6 0 3 2 2 0 3 4 1 7 8 6 5 4 5 8 "
                                  "6 3 0 7 2 1 7 6 1 8 5 2 3 0 4 1 7 4 3 6 5 2 8 0 6 3 5 0 2 8 1 4 7 0 8 2 1 7 4 6 5 3";

/// Test solution vector constant.
const std::vector<int> TestVecSolution = {5, 2, 6, 7, 0, 3, 4, 1, 8, 3, 4, 0, 2, 8, 1, 5, 7, 6, 8, 1, 7, 5, 4, 6, 0, 3,
    2, 2, 0, 3, 4, 1, 7, 8, 6, 5, 4, 5, 8, 6, 3, 0, 7, 2, 1, 7, 6, 1, 8, 5, 2, 3, 0, 4, 1, 7, 4, 3, 6, 5, 2, 8, 0, 6,
    3, 5, 0, 2, 8, 1, 4, 7, 0, 8, 2, 1, 7, 4, 6, 5, 3};

/**
 * Test fixture used to test the board.
 */
class SudokuBoardTest : public ::testing::Test
{
protected:

    /**
     * Test a sudoku board XML load capabilities.
     */
    void TestLoad(std::shared_ptr<SudokuBoard> board)
    {
        ASSERT_EQ(1, board->GetStartingRow());
        ASSERT_EQ(5, board->GetStartingCol());
        ASSERT_EQ(TestVecSolution, board->GetSolution());
    }

    /**
     * Tests the ability for a board to know which sections are inside its
     * boundaries
     */
    void TestInBoard(std::shared_ptr<SudokuBoard> board)
    {
        // Test right side
        ASSERT_FALSE(board->InBoard(14, 3));
        ASSERT_TRUE(board->InBoard(13, 3));

        // Test bottom side
        ASSERT_FALSE(board->InBoard(7, 10));
        ASSERT_TRUE(board->InBoard(7, 9));

        // Test left side
        ASSERT_FALSE(board->InBoard(4, 3));
        ASSERT_TRUE(board->InBoard(5, 3));

        // Test top side
        ASSERT_FALSE(board->InBoard(7, 0));
        ASSERT_TRUE(board->InBoard(7, 1));
    }
};

TEST_F(SudokuBoardTest, Construct)
{
    Level level(IDM_LEVEL_LEVEL2);
    SudokuBoard sudokuBoard(&level);
}

TEST_F(SudokuBoardTest, Load)
{
    Level level(IDM_LEVEL_LEVEL2);
    std::shared_ptr<SudokuBoard> board = level.GetBoard();
    TestLoad(board);
}

TEST_F(SudokuBoardTest, InBoard)
{
    Level level(IDM_LEVEL_LEVEL2);
    std::shared_ptr<SudokuBoard> board = level.GetBoard();
    TestInBoard(board);
}
