/**
 * @file Item.h
 * @author ethan
 *
 * Contains class that defines items.
 */


#ifndef PROJECT1_SUDOKULIB_ITEM_H
#define PROJECT1_SUDOKULIB_ITEM_H

#include "Declaration.h"

class Level;
class ItemVisitor;

/**
 * Base class for items in the sudoku game
 */
class Item
{
private:
    /// The game this item is contained in
    Level *mLevel;

    /// The declaration for the item.
    std::shared_ptr<Declaration> mDeclaration;

    double mRow = 0;     ///< Row location for lower left corner of item
    double mCol = 0;     ///< Col location for lower left corner of item

    /// The item id.
    std::wstring mId;

protected:
    /**
     * Constructor for items.
     * @param level The level this belongs to.
     */
    Item(Level* level) : mLevel(level) {}

public:

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;

    virtual ~Item();

    /**
     * Get the id for the item.
     * @return Get the id for the item.
     */
    std::wstring GetId() { return mId; }

    /**
     * The row of the item
     * @returns Row of the item
     */
    double GetRow() const { return mRow; }

    /**
     * The col of the item
     * @returns Col of the item
     */
    double GetCol() const { return mCol; }

    /**
     * Return value -1 as default
     * @return -1
     */
    virtual int GetValue() { return -1; }

    /**
     * Set the item location
     * @param col Col location
     * @param row Row location
     */
    virtual void SetLocation(double col, double row) { mCol = col; mRow = row; }

    /**
     * Getter for the declaration of this item.
     * @returns Declaration
     */
    std::shared_ptr<Declaration> GetDeclaration() { return mDeclaration; }

    /**
     * Setter for the declaration of this item.
     * @param declaration
     */
    void SetDeclaration(std::shared_ptr<Declaration> declaration) { mDeclaration = declaration; };

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    /**
    * Get the pointer to the level object
    * @return Pointer to level object
    */
    Level *GetLevel() { return mLevel;  }

    virtual void XmlLoad(wxXmlNode *);

    /**
     * Draws the item.
     * @param graphics The graphics context to draw on.
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) {};

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    virtual void Accept(ItemVisitor* visitor) = 0;

    bool TileHit(double column, double row);

    /**
     * Setter for SingleImageItems
     * @param val new value for digit objects
     */
    virtual void SetXRay(bool val) {}
};

#endif //PROJECT1_SUDOKULIB_ITEM_H
