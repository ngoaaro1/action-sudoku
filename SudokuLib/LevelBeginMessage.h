/**
 * @file LevelBeginMessage.h
 * @author Michael Plante
 *
 * Contains class that defines the messages at the beginning of the level
 */

#ifndef PROJECT1_SUDOKULIB_LEVELBEGINMESSAGE_H
#define PROJECT1_SUDOKULIB_LEVELBEGINMESSAGE_H

/**
 * Class defines the message that will be displayed at the beginning of a level
 */
class LevelBeginMessage {
private:
    ///Holds number of level
    std::wstring mLevelNum;
public:
    /// Default constructor (disabled)
    LevelBeginMessage() = default;

    /// Copy constructor (disabled)
    LevelBeginMessage(const LevelBeginMessage &) = delete;

    /// Assignment operator
    void operator=(const LevelBeginMessage &) = delete;

    /**
     * Constructor
     * @param level Number of level as wstring
     */
    LevelBeginMessage(std::wstring level) : mLevelNum(level) {}

    ///Draws message
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    /**
     * Setter for mLevelNum.
     * Used after determining the level file being loaded to set the level number that will display in beginning message.
     * @param level The level number as a wstring
     */
    void SetLevelNum(const std::wstring & level) { mLevelNum = level; }

};

#endif //PROJECT1_SUDOKULIB_LEVELBEGINMESSAGE_H
