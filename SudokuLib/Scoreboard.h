/**
 * @file Scoreboard.h
 * @author Michael Plante
 *
 * Contains the class that defines the scoreboard/timer for the game.
 */

#ifndef PROJECT1_SUDOKULIB_SCOREBOARD_H
#define PROJECT1_SUDOKULIB_SCOREBOARD_H

/**
 * Contains information about the time of the game.
 */
class Scoreboard {
private:
    ///The current time to display
    std::wstring mScoreboardText;

    ///Total time game has been playable in seconds
    double mTotalGameTime = 0;
    ///Minutes game has run
    int mMinutes = 0;
    ///Seconds game has run
    int mSeconds = 0;

    ///Calculates displayed time
    void CalculateTime(double elapsed);

public:
    ///Constructor
    Scoreboard() {}

    ///Reset scoreboard time
    void Reset();

    ///Draws text
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    ///Updates scoreboard
    void Update(double elapsed);

};

#endif //PROJECT1_SUDOKULIB_SCOREBOARD_H
