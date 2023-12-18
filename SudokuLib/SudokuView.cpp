/**
 * @file SudokuView.cpp
 * @author hankm
 */

#include "pch.h"
#include <memory>
#include <wx/dcbuffer.h>
#include <wx/dc.h>
#include "ids.h"
#include "SudokuView.h"
#include "SudokuGame.h"

using namespace std;

/// Frame duration in milliseconds for when timer is started
const int FrameDuration = 30;

/// BKey code pressed
const int BKey = 66;

/// Zero key code pressed
const int ZeroKey = 48;

/// One key code pressed
const int OneKey = 49;

/// Two key code pressed
const int TwoKey = 50;

/// Three key code pressed
const int ThreeKey = 51;

/// Four key code pressed
const int FourKey = 52;

/// Five key code pressed
const int FiveKey = 53;

/// Six key code pressed
const int SixKey = 54;

/// Seven key code pressed
const int SevenKey = 55;

/// Eight key code pressed
const int EightKey = 56;

/**
 * Initialize the sudoku view class.
 * @param mainFrame The parent window for this class.
 */
void SudokuView::Initialize(wxFrame* mainFrame)
{
    // Set up for virtual pixels, repainting everytime.
    Create(mainFrame, wxID_ANY,
           wxDefaultPosition, wxDefaultSize,
           wxFULL_REPAINT_ON_RESIZE);

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevelSolve, this,
                    IDM_LEVEL_SOLVE);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevelSetZero, this,
                    IDM_LEVEL_LEVEL0);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevelSetOne, this,
                    IDM_LEVEL_LEVEL1);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevelSetTwo, this,
                    IDM_LEVEL_LEVEL2);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevelSetThree, this,
                    IDM_LEVEL_LEVEL3);

    Bind(wxEVT_PAINT, &SudokuView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &SudokuView::OnLeftDown, this);
    Bind(wxEVT_KEY_DOWN, &SudokuView::OnKeyDown, this);

    //For animation, not needed yet
    Bind(wxEVT_TIMER, &SudokuView::OnTimer, this);

    //Begin timing
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    mStopWatch.Start();

}

/**
 * Draws the window given a paint event.
 * @param event The wxPaintEvent object.
 */
void SudokuView::OnPaint(wxPaintEvent& event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc =
        std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    mSudokuGame.Update(elapsed);

    // Tell the game class to draw
    wxRect rect = GetRect();
    mSudokuGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());

}

/**
 * Handle the left mouse button down event
 * @param event The wxMouseEvent object.
 */
void SudokuView::OnLeftDown(wxMouseEvent &event)
{
    mSudokuGame.OnLeftDown(event.GetX(), event.GetY());
}

/**
 * Handle the key button pressed down event
 * @param event The KeyEvent object.
 */
void SudokuView::OnKeyDown(wxKeyEvent &event)
{
    int pressed = event.GetKeyCode();
    switch(pressed)
    {
        case BKey:
            mSudokuGame.SpartyHeadbutt();
            break;
        case WXK_SPACE:
            mSudokuGame.SpartyEat();
            break;
        case ZeroKey:
            mSudokuGame.SpartyRegurgitate(0);
            break;
        case OneKey:
            mSudokuGame.SpartyRegurgitate(1);
            break;
        case TwoKey:
            mSudokuGame.SpartyRegurgitate(2);
            break;
        case ThreeKey:
            mSudokuGame.SpartyRegurgitate(3);
            break;
        case FourKey:
            mSudokuGame.SpartyRegurgitate(4);
            break;
        case FiveKey:
            mSudokuGame.SpartyRegurgitate(5);
            break;
        case SixKey:
            mSudokuGame.SpartyRegurgitate(6);
            break;
        case SevenKey:
            mSudokuGame.SpartyRegurgitate(7);
            break;
        case EightKey:
            mSudokuGame.SpartyRegurgitate(8);
            break;
        default:
            break;
    }
}

/**
* Handle the timer tick event
* @param event The wxTimerEvent event.
*/
void SudokuView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

/**
 * Handle Level 0 set event
 * @param event The wxCommandEvent
 */
void SudokuView::OnLevelSetZero(wxCommandEvent& event)
{
    mSudokuGame.SetLevel(IDM_LEVEL_LEVEL0);
    Refresh();
}

/**
 * Handle Level 1 set event
 * @param event The wxCommandEvent
 */
void SudokuView::OnLevelSetOne(wxCommandEvent& event)
{
    mSudokuGame.SetLevel(IDM_LEVEL_LEVEL1);
    Refresh();
}

/**
 * Handle Level 2 set event
 * @param event The wxCommandEvent
 */
void SudokuView::OnLevelSetTwo(wxCommandEvent& event)
{
    mSudokuGame.SetLevel(IDM_LEVEL_LEVEL2);
    Refresh();
}

/**
 * Handle Level 3 set event
 * @param event The wxCommandEvent
 */
void SudokuView::OnLevelSetThree(wxCommandEvent& event)
{
    mSudokuGame.SetLevel(IDM_LEVEL_LEVEL3);
    Refresh();
}

/**
 * Handles solve command, solve the current level.
 * @param event
 */
void SudokuView::OnLevelSolve(wxCommandEvent & event)
{
    mSudokuGame.SolveLevel();
}
