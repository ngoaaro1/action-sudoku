/**
 * @file Given.h
 * @author hankm
 *
 * Given numbers for sudoku.
 */

#ifndef PROJECT1_SUDOKULIB_GIVEN_H
#define PROJECT1_SUDOKULIB_GIVEN_H

#include "Item.h"
#include "SudokuGame.h"
#include "SingleImageItem.h"

/**
 * Given numbers for sudoku.
 */
class Given : public SingleImageItem
{
private:

public:
    /**
     * Constuctor for given.
     * @param level Level that this given belongs to.
     */
    Given(Level* level) : SingleImageItem(level) {};

    void Accept(ItemVisitor* visitor);

    int GetValue() override;
};

#endif //PROJECT1_SUDOKULIB_GIVEN_H
