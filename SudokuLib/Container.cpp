/**
 * @file Container.cpp
 * @author Devon FoxElster
 */

#include "pch.h"
#include <memory>
#include "Container.h"
#include "Digit.h"
#include "ItemVisitor.h"
#include "NumberDeclaration.h"
#include "GetDeclarationVisitor.h"
#include "ContainerDeclaration.h"


using namespace std;

/// Const for the Coordinate function. Digits are always 1 Column wide
double const DigitColumnWidth = 1;

/// Const for the Coordinate function. Digits are always 1 Row tall
double const DigitRowHeight = 1;

/// Scales the original dispersal zone (same size as the container) to
/// 2/3 of its size
double const DispersalZoneScale = (2.0 / 3.0);

/**
 * Constructor for the Container.
 * @param level The level the container belongs to.
 */
Container::Container(Level* level) : Item(level)
{
    std::random_device rd;
    mRandomGenerator.seed(rd());
}

/**
 * Draw a container item.
 * @param graphics Graphics context to draw on.
 */
void Container::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Retrieve the Declaration and Level for the relevant information
    auto declaration = GetDeclaration();
    GetDeclarationVisitor declarationVisitor;
    declaration->Accept(&declarationVisitor);
    auto containerDeclaration = declarationVisitor.GetContainerDeclaration();
    auto level = GetLevel();

    // Retrieve height, width, and tile sizes from the Declaration
    // and Levels associated with this object
    auto tileWidth = level->GetTileWidth();
    auto tileHeight = level->GetTileHeight();
    auto width = containerDeclaration->GetWidth();
    auto height = containerDeclaration->GetHeight();

    // Retrieve a vector containing both the front and back images
    // for the container
    auto imageVector = containerDeclaration->GetBitmaps();

    // Draw the back image first
    graphics->DrawBitmap(*imageVector.at(0),
                         int(Item::GetCol()*tileWidth),
                         int((Item::GetRow()+1)*tileHeight - height),
                         width, height);

    // Call the function drawing the vector of digits
    DrawDigits(graphics);

     // Draw the front image last
    graphics->DrawBitmap(*imageVector.at(1),
                         int(Item::GetCol()*tileWidth),
                         int((Item::GetRow()+1)*tileHeight - height),
                         width, height);
}

/**
 * Loads the relevant attributes for the node.
 * @param node The xml node.
 * @param declarationMap The map which gets declarations based off of ids.
 */
void Container::XmlLoad(wxXmlNode *node, unordered_map<wstring, shared_ptr<Declaration>>& declarationMap)
{
    Item::XmlLoad(node);

    auto child = node->GetChildren();
    for (; child; child=child->GetNext())
    {
        shared_ptr<Digit> item = make_shared<Digit>(Item::GetLevel());
        item->XmlLoad(child);
        item->SetDeclaration(declarationMap[child->GetAttribute(L"id").ToStdWstring()]);
        mStoredDigits.push_back(item);
    }
}

/**
 * Generates a random (x, y) coordinate pair for digits within the given zone
 *
 * @param minX minimum X value for the zone (in Column units)
 * @param maxY maximum Y value for the zone (in Row units)
 * @param height height of the zone (in Row units)
 * @param width width of the zone (in Column units)
 * @return Vector containing the <x, y> pair
 *
 * This function should be called with the bottom left corner of the
 * desired zone, with the height and width of the desired zone
 */
vector<double> Container::GenerateCoordinate(double minX, double maxY, double height, double width)
{

    uniform_real_distribution<> xDistribution(minX, minX + width - DigitColumnWidth);
    uniform_real_distribution<> yDistribution(maxY-height + DigitRowHeight, maxY);

    auto xCoord = xDistribution(mRandomGenerator);
    auto yCoord = yDistribution(mRandomGenerator);

    return {xCoord, yCoord};
}

/**
 * Loops through the items in a container's Stored Digits and draws each of them
 * @param graphics The graphics context to draw the items in
 */
void Container::DrawDigits(shared_ptr<wxGraphicsContext> graphics)
{
    auto item  = mStoredDigits.begin();
    for (; item != mStoredDigits.end(); ++item)
    {
        (*item)->Draw(graphics);
    }
}

/**
 * Receives an int value to check for inside of the container
 * @param number Value to search for inside the Contents
 * @return A pointer to the found value (If any)
 */
shared_ptr<Item> Container::SearchContents(int number)
{
    // Used for if an item is found that matches the number
    std::shared_ptr<Item> matchedNum = nullptr;

    auto num = mStoredDigits.begin();
    // Loops through contents
    for (; num != mStoredDigits.end(); ++num)
    {
        auto declaration = (*num)->GetDeclaration();
        GetDeclarationVisitor visitor2;
        declaration->Accept(&visitor2);
        auto numDec = visitor2.GetNumberDeclaration();
        if (numDec->GetValue() == number)
        {
            // With both values equal we found a match
            matchedNum = *num;
            break;
        }
    }
    return matchedNum;
}

/**
 * Deletes an item from the container
 * @param item Shared pointer to the item to delete
 */
void Container::DeleteItem(std::shared_ptr<Item> item)
{
    auto loc = std::find(mStoredDigits.begin(), mStoredDigits.end(), item);
    mStoredDigits.erase(loc);
}

/**
 * Checks the amount of items in the container
 * @return The number of items in the container
 */
int Container::CheckSize()
{

    return mStoredDigits.size();
}

/**
 * Moves all contents of a container onto a random area in the playing area above the container
 * May resize the digits to their proper playing area sizes
 * @param resize True if items need to have their size changed back to playing size, false otherwise
 */
void Container::DisperseContents(bool resize)
{
    // Retrieving pixel sizes for the tiles and container
    auto containerHeight = GetDeclaration()->GetHeight();
    auto containerWidth = GetDeclaration()->GetWidth();
    auto tileWidth = GetLevel()->GetTileWidth();
    auto tileHeight = GetLevel()->GetTileHeight();

    // Calculating the height and width for the dispersal zone
    auto zoneCol = GetCol();
    auto zoneRow = GetRow() - (containerHeight) / tileHeight;
    auto zoneWidth = containerWidth / tileWidth;
    auto zoneHeight = (containerHeight / tileHeight) * DispersalZoneScale;

    for(auto item : (mStoredDigits))
    {
        //If resize is necessary change the size of the digits being moved to their playing area sizes
        if (resize)
        {
            item->SetXRay(false);
        }
        auto coordinate = GenerateCoordinate(zoneCol, zoneRow, zoneHeight, zoneWidth);
        // generate new coordinates and set location
        auto itemCol = coordinate.at(0);
        auto itemRow = coordinate.at(1);
        GetLevel()->Add(item);
        item->SetLocation(itemCol, itemRow);
    }
    //Remove all pointers from the container
    mStoredDigits.clear();
}