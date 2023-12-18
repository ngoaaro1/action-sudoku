/**
 * @file ids.h
 * @author Aaron Ngo
 *
 * ID values for our program.
 */

#ifndef PROJECT1_SUDOKULIB_IDS_H
#define PROJECT1_SUDOKULIB_IDS_H
#include <wx/wx.h>

/**
 * Unique ids of the different items in the Sudoku Game
 */
enum IDs {
    IDM_LEVEL_LEVEL0 = wxID_HIGHEST + 1,
    IDM_LEVEL_LEVEL1,
    IDM_LEVEL_LEVEL2,
    IDM_LEVEL_LEVEL3,
    IDM_LEVEL_SOLVE
};

#endif //PROJECT1_SUDOKULIB_IDS_H
