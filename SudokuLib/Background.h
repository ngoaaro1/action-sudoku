/**
 * @file Background.h
 * @author hankm
 *
 * Declares the background class.
 */

#ifndef PROJECT1_SUDOKULIB_BACKGROUND_H
#define PROJECT1_SUDOKULIB_BACKGROUND_H

#include "Item.h"
#include "SudokuGame.h"
#include "SingleImageItem.h"

/**
 * Declares the background class.
 */
class Background : public SingleImageItem
{
private:

public:
    Background(Level* level);
};

#endif //PROJECT1_SUDOKULIB_BACKGROUND_H
