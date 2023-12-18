/**
 * @file SingleImageItem.cpp
 * @author hankm
 */

#include "pch.h"
#include "SingleImageItem.h"
#include "GetDeclarationVisitor.h"
#include "ItemVisitor.h"

/// Size modifier for when numbers are in the XRay
double const XRayModifier = 0.6;

/**
 * Draw a single image item, instructions are all the same.
 * @param graphics Graphics context to draw on.
 */
void SingleImageItem::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto level = GetLevel();
    auto tileWidth = level->GetTileWidth();
    auto tileHeight = level->GetTileHeight();

    auto declaration = GetDeclaration();
    GetDeclarationVisitor declarationVisitor;
    declaration->Accept(&declarationVisitor);
    auto singleImageDeclaration = declarationVisitor.GetSingleImageDeclaration();

    auto width = singleImageDeclaration->GetWidth();
    auto height = singleImageDeclaration->GetHeight();

    if (mIsInXRay)
    {
        width *= XRayModifier;
        height *= XRayModifier;
    }

    graphics->DrawBitmap(*(singleImageDeclaration->GetBitmap()),
                         int(Item::GetCol()*tileWidth),
                         int((Item::GetRow()+1)*tileHeight - height),
                         width, height);

}

/**
 * Accepts a visitor to the class
 * @param visitor visitor accessing the object
 */
void SingleImageItem::Accept(ItemVisitor *visitor)
{
    visitor->VisitSingleImageItem(this);
}
