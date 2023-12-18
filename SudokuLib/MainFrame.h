/**
 * @file MainFrame.h
 * @author hankm
 *
 * Creates the main window for the sudoku app.
 */

#ifndef PROJECT1_SUDOKULIB_MAINFRAME_H
#define PROJECT1_SUDOKULIB_MAINFRAME_H

class SudokuView;

/**
 * Creates the main window for the sudoku app.
 */
class MainFrame : public wxFrame
{
private:
    SudokuView* mSudokuView = nullptr; ///< Pointer to the SudkuView object
    void OnExit(wxCommandEvent&);
    void OnClose(wxCloseEvent&);
    void OnAbout(wxCommandEvent&);

public:
    void Initialize();

};

#endif //PROJECT1_SUDOKULIB_MAINFRAME_H
