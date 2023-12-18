/**
 * @file SudokuGame.h
 * @author hankm
 *
 * The Sudoku Game class, handles the play of the game.
 */

#ifndef PROJECT1_SUDOKULIB_SUDOKUGAME_H
#define PROJECT1_SUDOKULIB_SUDOKUGAME_H

#include <memory>
#include "Scoreboard.h"
#include "Level.h"

class Item;
class Declaration;

/**
 * The Sudoku Game class, handles the play of the game.
 */
class SudokuGame
{
private:
    /// The level object that controls the current level.
    Level mLevel;

    double mScale;  ///< Scaling factor for virtual pixels.
    double mXOffset;    ///< X offset for virtual pixels.
    double mYOffset;    ///< Y offset for virtual pixels.

public:
    SudokuGame();

    ///Sets level function
    void SetLevel(int level);

    ///Draw function
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    ///Mouse-click function
    void OnLeftDown(double x, double y);

    void Update(double elapsed);

    /**
     * Make Sparty perform headbutt action
     */
    void SpartyHeadbutt() { mLevel.SpartyHeadbutt(); }

    /**
     * Make Sparty regurgitate a number
     * @param number The number that Sparty will regurgitate
     */
    void SpartyRegurgitate(int number) { mLevel.SpartyRegurgitate(number); }

    /**
     * Make sparty eat in the level.
     */
    void SpartyEat() { mLevel.SpartyEat(); }

    /**
     * Solve the level.
     */
    void SolveLevel() { mLevel.Solve(); }
};

#endif //PROJECT1_SUDOKULIB_SUDOKUGAME_H
