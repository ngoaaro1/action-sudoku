/**
 * @file Digit.h
 * @author hankm
 *
 * Digits that are able to solve sudoku.
 */

#ifndef PROJECT1_SUDOKULIB_DIGIT_H
#define PROJECT1_SUDOKULIB_DIGIT_H

#include "SudokuGame.h"
#include "SingleImageItem.h"

class Item;

/**
 * Digits that are able to solve sudoku.
 */
class Digit : public SingleImageItem
{
private:

public:
    Digit(Level*);
    void Accept(ItemVisitor* visitor) override;

    int GetValue() override;

};

#endif //PROJECT1_SUDOKULIB_DIGIT_H
