/**
 * @file SingleImageItem.h
 * @author hankm
 *
 * Descendant of item for items that have only one image.
 */

#ifndef PROJECT1_SUDOKULIB_SINGLEIMAGEITEM_H
#define PROJECT1_SUDOKULIB_SINGLEIMAGEITEM_H

#include "Item.h"
#include "Level.h"
#include "SingleImageDeclaration.h"

class ItemVisitor;
class GetDigitVisitor;

/**
 * Descendant of item for items that have only one image.
 */
class SingleImageItem : public Item
{
private:
    /// bool to check if item is inside the xray
    bool mIsInXRay = false;

public:
    /**
     * Constructor for the SingleImageItem.
     * @param level The level it belongs too.
     */
    SingleImageItem(Level* level) : Item(level) {}

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void Accept(ItemVisitor* visitor) override;

    /**
     * Set the XRay Boolean for when the object is in an Xray
     * @param val new boolean value for the variable
     */
     void SetXRay(bool val) override { mIsInXRay = val; }
};

#endif //PROJECT1_SUDOKULIB_SINGLEIMAGEITEM_H
