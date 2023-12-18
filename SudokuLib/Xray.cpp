/**
 * @file Xray.cpp
 * @author Devon FoxElster
 */

#include "pch.h"
#include "Xray.h"
#include "ItemVisitor.h"
#include "SingleImageDeclaration.h"
#include "XRayDeclaration.h"
#include "GetDeclarationVisitor.h"

///Toxicity value at which all digits in Xray will be regurgitated
const double ToxicityThreshold = 7;



/**
 * Draw a Xray item.
 * @param graphics Graphics context to draw on.
 */
void Xray::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    // handle drawing for Xray image
    auto level = GetLevel();
    auto tileWidth = level->GetTileWidth();
    auto tileHeight = level->GetTileHeight();

    auto declaration = GetDeclaration();
    GetDeclarationVisitor declarationVisitor;
    declaration->Accept(&declarationVisitor);
    auto singleImageDeclaration = declarationVisitor.GetSingleImageDeclaration();

    auto width = singleImageDeclaration->GetWidth();
    auto height = singleImageDeclaration->GetHeight();

    graphics->DrawBitmap(*(singleImageDeclaration->GetBitmap()),
                         int(Item::GetCol()*tileWidth),
                         int((Item::GetRow()+1)*tileHeight - height),
                         width, height);

    // Iterate through items in xray contents and display them on top
    Container::DrawDigits(graphics);
}


/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void Xray::Accept(ItemVisitor *visitor)
{
    Container::Accept(visitor);
    visitor->VisitXray(this);
}
void Xray::AddItem(std::shared_ptr<Item> item)
{
    auto level = GetLevel();
    auto tileHeight = level->GetTileHeight();
    auto tileWidth = level->GetTileWidth();

    auto declaration = GetDeclaration();

    auto height = declaration->GetHeight() / tileHeight;
    auto width = declaration->GetWidth() / tileWidth;


    auto newCoords = GenerateCoordinate(GetCol(), GetRow(),
                                        height, width);

    item->SetLocation(newCoords.at(0), newCoords.at(1));

    item->SetXRay(true);

    Container::AddItem(item);
}
/**
 * Checks if the Xray is full
 * @return True if full, false otherwise
 */
bool Xray::CheckFull()
{
    auto currentCapacity = CheckSize();

    auto declaration = GetDeclaration();
    GetDeclarationVisitor declarationVisitor;
    declaration->Accept(&declarationVisitor);
    auto xRayDeclaration = declarationVisitor.GetXRayDeclaration();

    return (currentCapacity >= xRayDeclaration->GetCapacity());
}

/**
 * Checks if the Xray has digits in it
 * @return True if digits are in Xray, false otherwise
 */
bool Xray::CheckOccupied()
{
    auto currentCapacity = CheckSize();

    return (currentCapacity > 0);
}

/**
 * Updates the toxicity value of numbers in Xray
 * Toxicity value essentially equates to the amount of time digits are in the Xray
 * @param elapsed Time passed since last update
 */
void Xray::UpdateToxicity(double elapsed)
{
    //If there are no digits in the Xray at any point reset toxicity to 0
    if (!CheckOccupied())
    {
        mToxicity = 0;
    }
    //If there are digits in the Xray update toxicity and possibly regurgitate
    else
    {
        //Update toxicity
        mToxicity += elapsed;

        //Regurgitate if toxicity has met or exceeded threshold
        if (mToxicity >= ToxicityThreshold)
        {

            //Disperse the contents of the Xray onto the playing area
            DisperseContents(true);

            //Return the toxicity to 0
            mToxicity = 0;
        }
    }
}
