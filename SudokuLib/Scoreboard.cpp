/**
 * @file Scoreboard.cpp
 * @author Michael Plante
 */
#include "pch.h"
#include "Scoreboard.h"

/// Top left corner of the scoreboard in virtual pixels
const wxPoint ScoreboardTopLeft = wxPoint(10, 10);

/// Size of the scoreboard text in virtual pixels
const int ScoreboardTextSize = 64;

/// Constraint for max value that seconds with leading 0 can be
const int MaxSecondsWithLeadingZero = 9;

/// Size of margin on left side of scoreboard
const double LeftMargin = 17.5;

/**
 * Draws the scoreboard on the screen
 * @param graphics The drawing context
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    //Set the font for drawing
    wxFont font(wxSize(0, ScoreboardTextSize),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, wxColour(255, 255, 255));

    //Draw
    graphics->DrawText(mScoreboardText, ScoreboardTopLeft.x + LeftMargin, ScoreboardTopLeft.y);
}

/**
 * Updates the scoreboard timer
 * Converts calculated members into string form to display if timer is not paused
 * @param elapsed The in-game time in milliseconds
 */
void Scoreboard::Update(double elapsed)
{
    //Calculates new time values
    CalculateTime(elapsed);


    //Update string that displays of time
    mScoreboardText.clear();
    //Set minutes and colon
    mScoreboardText.append(std::to_wstring(mMinutes));
    mScoreboardText.append(L":");

    //Determine if seconds are double-digit or not
    if (mSeconds > MaxSecondsWithLeadingZero)
    {
        //If double-digit just add to display string
        mScoreboardText.append(std::to_wstring(mSeconds));
    }
    else
    {
        //If not double-digit add leading zero and then single digit to display string
        mScoreboardText.append(L"0");
        mScoreboardText.append(std::to_wstring(mSeconds));
    }
}

/**
 * Calculates total time in minutes and seconds that game has been playable
 * @param elapsed The time interval since the last update
 */
void Scoreboard::CalculateTime(double elapsed)
{
    //Convert stopwatch time to seconds
    mTotalGameTime += elapsed;

    //Calculate in-game minutes
    mMinutes = (int)(mTotalGameTime) / 60;

    //Calculate remaining seconds
    mSeconds = (int)(mTotalGameTime - ((double)(mMinutes) * 60));
}

/**
 * Resets all members that relate to time to zero
 */
void Scoreboard::Reset()
{
    mTotalGameTime = 0;
    mMinutes = 0;
    mSeconds = 0;
}


