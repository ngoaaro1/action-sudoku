/**
 * @file Item.cpp
 * @author ethan
 */

#include "pch.h"
#include "Item.h"
#include "SudokuGame.h"
#include "Level.h"

using namespace std;

/**
 * Destructor
 */
Item::~Item()
{

}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
    mId = node->GetAttribute(L"id", L"");
    node->GetAttribute(L"row", L"0").ToDouble(&mRow);
    node->GetAttribute(L"col", L"0").ToDouble(&mCol);
}

/**
 * Calculate whether the item is in the tile for a column and row. Inclusive on top & left,
 * non inclusive bottom & right.
 * @param column The left side of the tile to check.
 * @param row The top side of the tile to check.
 * @return True if the item falls within the bounds of the tile.
 */
bool Item::TileHit(double column, double row)
{
    double itemCol = GetCol();
    double itemRow = GetRow();

    if (column <= itemCol && itemCol < column + 1 && row <= itemRow && itemRow < row + 1)
    {
        return true;
    }
    return false;
}
