/**
 * @file SudokuView.h
 * @author hankm
 *
 * Creates the SudokuView class, which serves as the main game window.
 */

#ifndef PROJECT1_SUDOKULIB_SUDOKUVIEW_H
#define PROJECT1_SUDOKULIB_SUDOKUVIEW_H

#include "SudokuGame.h"
#include "Scoreboard.h"

/**
 * Creates the sudoku view class which serves as the main game window.
 */
class SudokuView : public wxWindow {
private:

    ///Object that describes the Sudoku game
    SudokuGame mSudokuGame;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// Game time in milliseconds
    long mTime = 0;

    ///Paint event
    void OnPaint(wxPaintEvent&);

public:
    void Initialize(wxFrame* mainFrame);

    ///Left mouse button pressed event
    void OnLeftDown(wxMouseEvent& event);

    ///Key pressed event
    void OnKeyDown(wxKeyEvent& event);

    ///Timer event
    void OnTimer(wxTimerEvent &event);

    void OnLevelSolve(wxCommandEvent&);

    void OnLevelSetZero(wxCommandEvent&);
    void OnLevelSetOne(wxCommandEvent&);
    void OnLevelSetTwo(wxCommandEvent&);
    void OnLevelSetThree(wxCommandEvent&);

    /**
     * Stops timer so that window is closed
     */
    void StopTimer() { mTimer.Stop(); }
};

#endif //PROJECT1_SUDOKULIB_SUDOKUVIEW_H
