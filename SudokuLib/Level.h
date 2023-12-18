/**
 * @file Level.h
 * @author hankm
 *
 * Stores the data for the level.
 */

#ifndef PROJECT1_SUDOKULIB_LEVEL_H
#define PROJECT1_SUDOKULIB_LEVEL_H

#include "Item.h"
#include "Scoreboard.h"
#include "SudokuBoard.h"
#include "LevelBeginMessage.h"
#include "LevelEndMessage.h"
#include "Alert.h"

class Sparty;

/**
 * Stores the data for the level.
 */
class Level
{
private:

    ///The scoreboard/timer for the level
    std::shared_ptr<Scoreboard> mScoreboard;

    /// The sudoku board which is used for operations relating to board.
    std::shared_ptr<SudokuBoard> mSudokuBoard;

    int mLevelNumber; ///< The number of the current level.

    std::vector<std::shared_ptr<Item>> mItems;  ///< All items in the level

    std::shared_ptr<Sparty> mSparty;    ///< The Sparty item for the level

    int mWidth; ///< The width of the game for virtual pixels.
    int mHeight;    ///< The height of the game for virtual pixels.
    int mTileWidth; ///< The width of the virtual pixels.
    int mTileHeight;    ///< The height of the virtual pixels.

    std::shared_ptr<LevelBeginMessage> mLevelBeginMessage;   ///< Class that draws the beginning message for the level.
    std::shared_ptr<LevelEndMessage> mLevelEndMessage;   ///< Class that draws the ending message for the level.

    double mElapsed;   ///< Keeps track of elapsed time so we can display messages appropriately.
    bool mSolved;   ///< Bool to determine if game is solved
    bool mDone;     ///< Bool to determine if the level is complete

    std::vector<std::shared_ptr<Alert>> mAlerts;    ///< Alerts for the level.

public:
    Level(int level);

    /**
     * Get the width of a tile.
     * @return The tile width.
     */
    int GetTileWidth() { return mTileWidth; }

    /**
     * Get the height of a tile.
     * @return The tile height.
     */
    int GetTileHeight() { return mTileHeight; }

    /**
     * Get the pixel width of the screen which is just width*tile width.
     * @return Pixel width.
     */
    int GetPixelWidth() { return mWidth*mTileWidth; }

    /**
     * Get the pixel height of the screen which is just height*tile height.
     * @return
     */
    int GetPixelHeight() { return mHeight*mTileHeight; }

    /**
     * Getter for the level number currently being played.
     * @return Level number.
     */
    int GetLevel() { return mLevelNumber; }

    /**
     * Get the items for the level.
     * @return Items pointer.
     */
    std::vector<std::shared_ptr<Item>>* GetItems() { return &mItems; }

    /**
     * Get the Board for the level
     * @return the Sudoku Board
     */
    std::shared_ptr<SudokuBoard> GetBoard() { return mSudokuBoard; }

    void SetLevel(int level);

    wxString GetLevelFile();

    void CheckSolve();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void Add(std::shared_ptr<Item> item);

    void Clear();

    void Load();

    void OnLeftDown(double x, double y);

    void Update(double elapsed);

    void XmlDeclaration(wxXmlNode* node, std::unordered_map<std::wstring,
                        std::shared_ptr<Declaration>>& declarationMap);

    void XmlGame(wxXmlNode* node);

    void XmlItem(wxXmlNode* node, std::unordered_map<std::wstring, std::shared_ptr<Declaration>>& declarationMap);

    void Accept(ItemVisitor* visitor);

    void SpartyHeadbutt();

    void SpartyRegurgitate(int number);

    void SpartyEat();

    void Solve();

    void NextLevel();

    void AlertSpaceTaken();

    void AlertFull();

    void RemoveOldAlerts();
};

#endif //PROJECT1_SUDOKULIB_LEVEL_H
