/**
 * @file SudokuBoard.cpp
 * @author hankm
 */

#include "pch.h"
#include <sstream>
#include "SudokuBoard.h"
#include "GetDigitVisitor.h"
#include "NumberEvaluator.h"

using namespace::std;

/// The number of columns in a Sudoku board
const int BoardWidthHeight = 8;

/**
 * Constructor for board class.
 * @param level The level to initialize with.
 */
SudokuBoard::SudokuBoard(Level* level)
{
    mLevel = level;
    mStartingRow = 0;
    mStartingCol = 0;
    mSolution = {};
}

/**
 * Check if the level is solved.
 * @return True if solved, False Otherwise.
 */
bool SudokuBoard::Solve()
{
    auto items = mLevel->GetItems();

    int boardRow = 0;
    int boardCol = 0;

    for (int value : mSolution)
    {
        if (HitTest(boardCol + mStartingCol,
                            boardRow + mStartingRow) == nullptr)
        {
            GetDigitVisitor visitor(value);

            for(auto item : *items)
            {
                item->Accept(&visitor);
                if (visitor.GetDigit() != nullptr)
                {
                    // If a number is not in the board
                    if (!InBoard(item->GetCol(), item->GetRow()))
                    {
                        break;
                    }
                    visitor.Reset();
                }
            }

            Digit *digit = visitor.GetDigit();
            if (digit != nullptr)
            {
                digit->SetLocation(boardCol + mStartingCol, boardRow + mStartingRow);
            }
        }

        // Reaches the end of the row
        if (boardCol == BoardWidthHeight)
        {
            boardCol = 0;
            boardRow++;
        }
        else
        {
            boardCol++;
        }
    }

    return IsSolved();
}

/**
 * Check if the board is solved.
 * @return True if solved, false otherwise.
 */
bool SudokuBoard::IsSolved()
{
    int boardRow = 0;
    int boardCol = 0;

    for (int value : mSolution)
    {
        shared_ptr<Item> item = HitTest(boardCol + mStartingCol,boardRow + mStartingRow);

        if (item == nullptr || item->GetValue() != value)
        {
            return false;
        }

        if (boardCol == 8)
        {
            boardCol = 0;
            boardRow += 1;
        }
        else
        {
            boardCol += 1;
        }
    }

    return true;
}

/**
 * Load the Game XML data into board.
 * @param node The node to extract data from.
 */
void SudokuBoard::XmlLoad(wxXmlNode* node)
{
    mSolution.clear();
    node->GetAttribute(L"row").ToDouble(&mStartingRow);
    node->GetAttribute(L"col").ToDouble(&mStartingCol);
    stringstream stringStream(node->GetChildren()->GetContent().ToStdString());

    string number;
    while (stringStream >> number)
    {
        mSolution.push_back(stoi(number));
    }
}

/**
 * Check if a column and row pair falls with the board.
 * @param col The column coordinate (X).
 * @param row The row coordinate (Y).
 * @return True if within the confines of the board, False otherwise.
 */
bool SudokuBoard::InBoard(double col, double row)
{
    if (mStartingCol <= col && col <= mStartingCol + BoardWidthHeight)
    {
        if (mStartingRow <= row && row <= mStartingRow + BoardWidthHeight)
        {
            return true;
        }
    }
    return false;
}

/**
 * Check if a digit or given is in the specified board tile.
 * @param col The left side of the tile.
 * @param row The top side of the tile.
 * @return The item found if valid, otherwise nullptr.
 */
std::shared_ptr<Item> SudokuBoard::HitTest(double col, double row)
{
    auto items = mLevel->GetItems();
    for (auto item = items->rbegin(); item != items->rend(); ++item)
    {
        if ((*item)->TileHit(col, row))
        {
            NumberEvaluator visitor;
            (*item)->Accept(&visitor);
            if (visitor.GetFoundNumber())
            {
                return *item;
            }
        }
    }
    return nullptr;
}

/**
 * Checks if the board has been filled with numbers.
 * @return True if filled, false otherwise.
 */
bool SudokuBoard::IsFull()
{
    for (int row = 0; row <= BoardWidthHeight; ++row)
    {
        for (int col = 0; col <= BoardWidthHeight; ++col)
        {
            if (HitTest(col + mStartingCol,row + mStartingRow) == nullptr)
            {
                return false;
            }
        }
    }

    return true;
}
