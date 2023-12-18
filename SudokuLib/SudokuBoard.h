/**
 * @file SudokuBoard.h
 * @author hankm
 *
 * Contains the SudokuBoard class for Solve checks
 */

#ifndef PROJECT1_SUDOKULIB_SUDOKUBOARD_H
#define PROJECT1_SUDOKULIB_SUDOKUBOARD_H

#include "Item.h"
class Level;

/**
 * Sudoku Board class abstracts functions that involve solving
 */
class SudokuBoard
{
private:
    /// The row that the board starts at.
    double mStartingRow;

    /// The column that the board starts at.
    double mStartingCol;

    /// The solution to the sudoku game.
    std::vector<int> mSolution;

    /// Pointer to the level.
    Level* mLevel;

public:

    SudokuBoard(Level* level);

    bool Solve();

    bool IsFull();

    bool IsSolved();

    void XmlLoad(wxXmlNode *node);

    std::shared_ptr<Item> HitTest(double col, double row);
    bool InBoard(double col, double row);

    /**
     * Getter for the start row of the board
     * @return Row value
     */
    double GetStartingRow() { return mStartingRow; }

    /**
     * Getter for the start column of the board
     * @return Column value
     */
    double GetStartingCol() { return mStartingCol; };

    /**
     * Returns the solution of the sudoku board
     * @return mSolution
     */
    std::vector<int> GetSolution() { return mSolution; }
};

#endif //PROJECT1_SUDOKULIB_SUDOKUBOARD_H
