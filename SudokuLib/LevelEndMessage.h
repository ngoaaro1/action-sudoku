/**
 * @file LevelEndMessage.h
 * @author Michael Plante
 *
 * Contains class that defines messages for ends of levels
 */

#ifndef PROJECT1_SUDOKULIB_LEVELENDMESSAGE_H
#define PROJECT1_SUDOKULIB_LEVELENDMESSAGE_H

/**
 * The end of level message.
 */
class LevelEndMessage {
private:
    /// Message that displays at the end of each level
    std::wstring mMessage;

public:

    /// Copy constructor (disabled)
    LevelEndMessage(const LevelEndMessage &) = delete;

    /// Assignment operator
    void operator=(const LevelEndMessage &) = delete;

    /// Constructor
    LevelEndMessage();

    ///Draws message
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void SetFailureStatus();
    void SetSuccessStatus();
};

#endif //PROJECT1_SUDOKULIB_LEVELENDMESSAGE_H
