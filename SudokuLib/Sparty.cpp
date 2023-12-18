/**
 * @file Sparty.cpp
 * @author Devon FoxElster
 */

#include "pch.h"
#include "Sparty.h"
#include "SpartyDeclaration.h"
#include "GetDeclarationVisitor.h"
#include "ItemVisitor.h"
#include "GetItemVisitor.h"
#include "Xray.h"
#include "XRayDeclaration.h"
#include "Digit.h"
#include "NumberDeclaration.h"
#include "XRayRetrieveVisitor.h"


/// Character speed in pixels per second
const double MaxSpeed = 400.00;

/// The time for a mouth movement cycle in seconds
const double MouthRotationTime = 0.5;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.5;

/// Column offset for when Sparty spits a number outside of the Board
const double RegurgitateOffsetCol = 0.4;

/// Row offset for when Sparty spits a number outside of the board
const double RegurgitateOffsetRow = 0.5;

/// General offset for Sparty movement
double BorderOffset = 0.01;

/// The angle that Sparty's head and mouth are turned to initially
const double InitialAngle = 0;


/**
 * Constructor for Sparty.
 * @param level The level the xray belongs to.
 */
Sparty::Sparty(Level* level) : Item(level)
{

}

/**
 * Draw Sparty.
 * @param graphics Graphics context to draw on.
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto level = GetLevel();
    auto tileWidth = level->GetTileWidth();
    auto tileHeight = level->GetTileHeight();

    auto declaration = GetDeclaration();
    GetDeclarationVisitor declarationVisitor;
    declaration->Accept(&declarationVisitor);
    auto spartyDeclaration = declarationVisitor.GetSpartyDeclaration();

    auto width = spartyDeclaration->GetWidth();
    auto height = spartyDeclaration->GetHeight();
    auto front = spartyDeclaration->GetFront();

    //Head is drawn last
    if (front == 1) {

        //Headbutt animation sequence is occurring
        if (mHeadbutting)
        {
            //Get head pivot point
            wxPoint headPivot = wxPoint(spartyDeclaration->GetHeadPivotX() + int(Item::GetCol()*tileWidth),
                                        spartyDeclaration->GetHeadPivotY() + int((Item::GetRow()+1)*tileHeight - height));

            graphics->PushState();

            graphics->Translate(headPivot.x, headPivot.y);
            graphics->Rotate(mCurrentAngle);
            graphics->Translate(-headPivot.x, -headPivot.y);

            //Draw both to be rotated
            graphics->DrawBitmap(*(spartyDeclaration->GetMouthBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);

            graphics->DrawBitmap(*(spartyDeclaration->GetHeadBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);

            graphics->PopState();

        }
        //Eating animation sequence is occurring
        else if (mEating)
        {
            //Get mouth pivot point

            wxPoint mouthPivot = wxPoint(spartyDeclaration->GetMouthPivotX() + int(Item::GetCol()*tileWidth),
                                        spartyDeclaration->GetMouthPivotY() + int((Item::GetRow()+1)*tileHeight - height));

            graphics->PushState();

            graphics->Translate(mouthPivot.x, mouthPivot.y);
            graphics->Rotate(mCurrentAngle);
            graphics->Translate(-mouthPivot.x, -mouthPivot.y);

            //Draw both to be rotated
            graphics->DrawBitmap(*(spartyDeclaration->GetMouthBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);

            graphics->PopState();
            graphics->DrawBitmap(*(spartyDeclaration->GetHeadBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);
        }
        //No animations
        else
        {
            graphics->DrawBitmap(*(spartyDeclaration->GetMouthBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);

            graphics->DrawBitmap(*(spartyDeclaration->GetHeadBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);
        }

    }
    //Mouth is drawn last
    if (front == 2) {

        //Headbutt animation sequence is occurring
        if (mHeadbutting)
        {
            //Get head pivot point
            wxPoint headPivot = wxPoint(spartyDeclaration->GetHeadPivotX() + int(Item::GetCol()*tileWidth),
                                        spartyDeclaration->GetHeadPivotY() + int((Item::GetRow()+1)*tileHeight - height));

            graphics->PushState();

            graphics->Translate(headPivot.x, headPivot.y);
            graphics->Rotate(mCurrentAngle);
            graphics->Translate(-headPivot.x, -headPivot.y);

            //Draw both to be rotated
            graphics->DrawBitmap(*(spartyDeclaration->GetHeadBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);

            graphics->DrawBitmap(*(spartyDeclaration->GetMouthBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);

            graphics->PopState();

        }
            //Eating animation sequence is occurring
        else if (mEating || mRegurgitating)
        {

            //Get mouth pivot point

            wxPoint mouthPivot = wxPoint(spartyDeclaration->GetMouthPivotX() + int(Item::GetCol()*tileWidth),
                                         spartyDeclaration->GetMouthPivotY() + int((Item::GetRow()+1)*tileHeight - height));

            graphics->PushState();

            graphics->Translate(mouthPivot.x, mouthPivot.y);
            graphics->Rotate(mCurrentAngle);
            graphics->Translate(-mouthPivot.x, -mouthPivot.y);

            //Draw both to be rotated
            graphics->DrawBitmap(*(spartyDeclaration->GetMouthBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);

            graphics->PopState();
            graphics->DrawBitmap(*(spartyDeclaration->GetHeadBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);
        }
            //No animations
        else
        {
            graphics->DrawBitmap(*(spartyDeclaration->GetHeadBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);

            graphics->DrawBitmap(*(spartyDeclaration->GetMouthBitmap()),
                                 int(Item::GetCol()*tileWidth),
                                 int((Item::GetRow()+1)*tileHeight - height),
                                 width, height);
        }

    }

}

/**
 * Handle updates in time of our Sparty
 *
 * This is called before we draw and allows us to
 * move our Sparty. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Sparty::Update(double elapsed)
{
    // level sparty is on
    auto level = GetLevel();

    // sparty declaration visitor
    auto declaration = GetDeclaration();
    GetDeclarationVisitor visitor;
    declaration->Accept(&visitor);
    auto spartyDec = visitor.GetSpartyDeclaration();

    double tileWidth = level->GetTileWidth();
    double tileHeight = level->GetTileHeight();
    double backgroundWidth = level->GetPixelWidth()/tileWidth;
    double backgroundHeight = level->GetPixelHeight()/tileHeight;
    double spartyHeight = spartyDec->GetSpartyHeight();


    //If an animation is occurring update the angle of rotation
    if (mHeadbutting || mEating || mRegurgitating)
    {
        //Updates angle of the current animation (head movement or mouth movement)
        CalculateAngle(elapsed);

        //Once headbutt angle is reached perform headbutt operation on a container in range
        if (mHeadbutting && (spartyDec->GetHeadPivotAngle() <= mCurrentAngle))
        {
            PerformHeadbutt();
        }

        //Once mouth angle is reached perform eating operation on a container in range
        if (mEating && (spartyDec->GetMouthPivotAngle() <= mCurrentAngle))
        {
            PerformEat();
        }

        //Once mouth angle is reached perform regurgitation operation
        if (mRegurgitating && (spartyDec->GetMouthPivotAngle() <= mCurrentAngle))
        {
            PerformRegurgitate();
        }

    }

    double newDestinationX = GetCol() + mSpeedX / tileWidth * elapsed;
    double newDestinationY = GetRow() + mSpeedY / tileHeight * elapsed;


    bool XDestination = abs(mDestinationX - GetCol()) < abs(mSpeedX/tileWidth*elapsed);
    bool YDestination = abs(mDestinationY - GetRow()) < abs(mSpeedY/tileWidth*elapsed);

    // when sparty travels past the left border, he will stop and set to the offset from the left of the border
    if( newDestinationX <= 0)
    {
        mSpeedX = 0;
        mSpeedY = 0;
        SetLocation(BorderOffset,GetRow());
    }

    // when sparty's left side travels past 2 tiles from the right side, he will stop and be set to the offset + 2 tiles from the right side
    else if ( newDestinationX >= backgroundWidth - 2)
    {
        mSpeedX = 0;
        mSpeedY = 0;
        SetLocation(backgroundWidth - (2 + BorderOffset),GetRow());
    }

    // when sparty goes above the top border, he will stop and be set the offset from the top
    else if ( newDestinationY <= 0)
    {
        mSpeedX = 0;
        mSpeedY = 0;
        SetLocation(GetCol(),BorderOffset);
    }

    // when the bottom of sparty hits the bottom of the border, the bottom of sparty will be set an offset from the bottom
    else if ( (newDestinationY + spartyHeight/(2*tileHeight)) >= backgroundHeight)
    {
        mSpeedX = 0;
        mSpeedY = 0;
        SetLocation(GetCol(),backgroundHeight - spartyHeight/(2*tileHeight) - BorderOffset);
    }
    // when sparty passes the destination, speed will be 0, and he will be set to the destination
    else if ( XDestination || YDestination)
    {
        mSpeedX = 0;
        mSpeedY = 0;
        SetLocation(mDestinationX, mDestinationY);
    }
    // if no stoppages, set sparty to the new location
    else
    {
        SetLocation(newDestinationX,newDestinationY);
    }
}

/**
 * Event Controller function that assigns a destination point for
 * the Sparty to move toward
 * @param x destination X coordinate
 * @param y destination Y coordinate
 * @param tileWidth The pixel width of every tile
 * @param tileHeight The pixel height of every tile
 */
void Sparty::OnLeftDown(double x, double y, int tileWidth, int tileHeight)
{
    auto declaration = GetDeclaration();
    GetDeclarationVisitor visitor;
    declaration->Accept(&visitor);
    auto spartyDec = visitor.GetSpartyDeclaration();
    double targetX = spartyDec->GetTargetX();
    double targetY = spartyDec->GetTargetY();

    // The destination coordinates adjusted for the offset of Sparty's
    // target x and y coordinates (in Column and Row units)
    double destinationX = (x-targetX)/tileWidth;
    double destinationY = (y-targetY)/tileHeight;

    // if the Destination x is not the current column
    // and the Destination y is not the current row
    if (!(destinationX == GetCol() && destinationY == GetRow()))
    {
        // Assign the destination member variables to the current units
        SetDestination(destinationX,destinationY);

        double spartyX = destinationX*tileWidth-GetCol()*tileWidth;
        double spartyY = destinationY*tileHeight-GetRow()*tileHeight;

        double hypotenuse = sqrt(spartyX*spartyX+spartyY*spartyY);
        double unitX = spartyX/hypotenuse;
        double unitY = spartyY/hypotenuse;

        ChangeSpeed(MaxSpeed*unitX,MaxSpeed*unitY);
    }

}

/**
 * Initiates Sparty into the headbutting state.
 */
void Sparty::Headbutt()
{
    if ((mSpeedX == 0) && (mSpeedY == 0) && (!mEating) && (!mRegurgitating))
    {
        mHeadbutting = true;
        mCurrentAngle = InitialAngle;
        mRotatingClockwise = true;
    }
}

/**
 * Returns a bool representing whether Sparty is close enough to a container to headbutt it.
 * @param item The item we are testing.
 * @returns bool representing whether Sparty is close enough to an item to headbutt it.
 */
bool Sparty::HeadbuttHitTest(Item * item) {
    GetItemVisitor itemVisitor;
    item->Accept(&itemVisitor);
    auto container = itemVisitor.GetContainer();
    auto xray = itemVisitor.GetXray();

    // Checks that the item is a container and NOT the Xray
    if (container != nullptr && xray == nullptr) {

        auto spartyCol = GetCol();
        auto spartyRow = GetRow();
        auto spartyHeight = GetDeclaration()->GetHeight();
        // Y location of bottom of the Sparty image
        auto spartyY = (spartyRow+1)*GetLevel()->GetTileHeight() - spartyHeight;

        auto containerCol = container->GetCol();
        auto containerRow = container->GetRow();
        auto containerHeight = container->GetDeclaration()->GetHeight();
        // Y location of the bottom of the container image
        auto containerY = (containerRow+1)*GetLevel()->GetTileHeight() - containerHeight;


        if ((abs(spartyCol - containerCol) <= 2.5) && (spartyY >= containerY && spartyY <= containerY + containerHeight)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}


/**
 * When a number button is pressed this function checks whether Sparty
 * can spit that number
 * @param number number of the Digit to be regurgitated
 */
void Sparty::Regurgitate(int number)
{
    if ((mSpeedX == 0) && (mSpeedY == 0) && (!mHeadbutting)) {
        // Visitor to find the XRay
        XRayRetrieveVisitor visitor1;
        GetLevel()->Accept(&visitor1);
        auto xRay = visitor1.ReturnXRay();

        // Look for whether the number exists in the stomach
        mNumToRegurgitate = xRay->SearchContents(number);

        // Retrieve the Declaration associated with this Sparty
        auto declaration  = GetDeclaration();
        GetDeclarationVisitor visitor3;
        declaration->Accept(&visitor3);
        auto spartyDec = visitor3.GetSpartyDeclaration();
        // if we have a match in the contents
        if (mNumToRegurgitate != nullptr)
        {
            // If the number can be regurgitated
            mRegurgitating = true;

            auto level = mNumToRegurgitate->GetLevel();
            auto board = level->GetBoard();
            // The board  is 9x9, as the numbers range from 0->8
            double const TileCount = 9;

            // Computing the Column and Row numbers of the Sparty Target
            auto numColumn = GetCol() +
                // this calculates the distance from Target X to the left corner
                // in Column units
                spartyDec->GetTargetX() / level->GetTileWidth();
            auto numRow = GetRow() +
                // this calculates the distance from Target Y to the bottom corner
                // in Row units
                spartyDec->GetTargetY() / level->GetTileHeight();

            // If the Regurgitate location is inside the board
            // I.E. left bound <= current <= right bound
            // upper bound <= current <= lower bound
            auto rightBound = board->GetStartingCol()+TileCount;
            auto lowerBound = board->GetStartingRow()+TileCount;
            bool colCheck = ((board->GetStartingCol() <= numColumn)
                && numColumn <= rightBound);
            bool rowCheck = ((board->GetStartingRow() <= numRow)
                && numRow <= lowerBound);

            // If within the Board is true
            if (colCheck && rowCheck)
            {
                // Truncates the column and row values
                numColumn = floor(numColumn);
                numRow = floor(numRow);

                auto locationTest = board->HitTest(numColumn, numRow);
                // if there is a number currently on the board
                if (locationTest != nullptr)
                {
                    level->AlertSpaceTaken();
                    mRegurgitating = false;
                    return;
                }

            }
            else
            {
                numColumn -= RegurgitateOffsetCol;
                numRow -= RegurgitateOffsetRow;
            }

            //Store final calculated column and row location for regurgitation
            mRegurgitateCol = numColumn;
            mRegurgitateRow = numRow;

            //If Sparty is currently eating reset the animation and cease eating
            if (mEating)
            {
                mEating = false;
                mRotatingClockwise = true;
                mCurrentAngle = InitialAngle;
            }

        }
    }
}

/**
 * Called when Sparty attempts to eat a digit. Sets Sparty into eating state.
 */
void Sparty::Eat()
{
    // sparty declaration visitor
    auto declaration = GetDeclaration();
    GetDeclarationVisitor visitor;
    declaration->Accept(&visitor);
    auto spartyDec = visitor.GetSpartyDeclaration();

    if ((mSpeedX == 0) && (mSpeedY == 0) && (!mHeadbutting))
    {
        if (mRegurgitating && mCurrentAngle < spartyDec->GetMouthPivotAngle() && mRotatingClockwise)
        {
            mEating = false;
            mRotatingClockwise = true;
            mCurrentAngle = InitialAngle;
        }
        else
        {
            mEating = true;
            mCurrentAngle = InitialAngle;
            mRotatingClockwise = true;
        }
    }
}

/**
 * Returns a bool representing whether Sparty is close enough to an item to eat it.
 * @param item The item we are testing.
 * @returns bool representing whether Sparty is close enough to an item to eat it.
 */
bool Sparty::EatHitTest(Item * item) {
    GetItemVisitor itemVisitor;
    item->Accept(&itemVisitor);
    auto digit = itemVisitor.GetDigit();

    if (digit != nullptr && mSpeedX == 0 && mSpeedY == 0) {

        auto digitCol = digit->GetCol();
        auto digitRow = digit->GetRow();

        // Testing on the tile 1 to the right of Sparty
        auto spartyCol = GetCol() + 1;
        auto spartyRow = GetRow();

        // Distance calculations
        double term1 = pow(spartyCol - digitCol, 2);
        double term2 = pow(spartyRow - digitRow, 2);
        double distance = sqrt(term1 + term2);
        if (distance <= .5) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

void Sparty::Accept(ItemVisitor *visitor)
{
    visitor->VisitSparty(this);
}

/**
 * Calculates the new angle Sparty should be rotated to and updates rotation members accordingly
 * Function is capable of changing the direction of movement for the rotation and of ending the animation sequence
 * @param elapsed Time elapsed since last update
 */
void Sparty::CalculateAngle(double elapsed)
{

    auto declaration = GetDeclaration();
    GetDeclarationVisitor declarationVisitor;
    declaration->Accept(&declarationVisitor);
    auto spartyDec = declarationVisitor.GetSpartyDeclaration();

    //Determine rotation speed
    double rotationSpeed;

    if (mHeadbutting)
    {
        rotationSpeed = (2 * spartyDec->GetHeadPivotAngle()) / HeadbuttTime;
    }
    else
    {
        rotationSpeed = (2 * spartyDec->GetMouthPivotAngle()) / MouthRotationTime;
    }

    //Set correct direction of rotation if rotation is in counterclockwise direction
    if (!mRotatingClockwise)
    {
        rotationSpeed *= -1;
    }

    //Update current angle
    mCurrentAngle += rotationSpeed * elapsed;

    //Change direction of rotation of the radian limit has been reached
    if (mHeadbutting && (mCurrentAngle >= spartyDec->GetHeadPivotAngle()))
    {
        mRotatingClockwise = false;
    }

    if ((mEating || mRegurgitating) && (mCurrentAngle >= spartyDec->GetMouthPivotAngle()))
    {
        mRotatingClockwise = false;
    }

    //Stop rotation if animation is complete
    if (mCurrentAngle <= InitialAngle)
    {
        mHeadbutting = false;
        mEating = false;
        mRegurgitating = false;
        mRotatingClockwise = true;
        mCurrentAngle = InitialAngle;
    }

}

/**
 * Releases numbers from a container within range of a headbutt
 */
void Sparty::PerformHeadbutt()
{
    //Container interactions may go here

    auto items = GetLevel()->GetItems();
    Container * brokenContainer = nullptr;
    GetItemVisitor itemVisitor;
    for (auto item: *items) {
        if (HeadbuttHitTest(item.get())) {
            item->Accept(&itemVisitor);
            brokenContainer = itemVisitor.GetContainer();
        }
    }

    if (brokenContainer != nullptr) {
        // Add contents to the level
        brokenContainer->DisperseContents(false);
    }
}

/**
 * Moves number within range into Xray if Xray is not full.
 */
void Sparty::PerformEat()
{
    GetItemVisitor itemVisitor;
    GetLevel()->Accept(&itemVisitor);
    auto xray = itemVisitor.GetXray();

    auto items = GetLevel()->GetItems();
    std::shared_ptr<Item> eatenItem = nullptr;
    for (auto item: *items) {
        if (EatHitTest(item.get())) {
            if (!xray->CheckFull()) {
                eatenItem = item;
            }
            else {
                GetLevel()->AlertFull();
            }
        }
    }

    if (eatenItem != nullptr) {
        // Add the eaten item to xray's contents
        xray->AddItem(eatenItem);

        // Remove the eaten item from level's items
        auto loc = find(begin(*items), end(*items), eatenItem);
        if (loc != end(*items))
        {
            items->erase(loc);
        }
    }
}

/**
* Moves a number out of the Xray and onto the playing area
*/
void Sparty::PerformRegurgitate()
{
    // Visitor to find the XRay
    XRayRetrieveVisitor visitor1;
    GetLevel()->Accept(&visitor1);
    auto xRay = visitor1.ReturnXRay();

    if (mNumToRegurgitate != nullptr)
    {
        auto level = mNumToRegurgitate->GetLevel();

        // Assign the location to the number
        mNumToRegurgitate->SetLocation(mRegurgitateCol, mRegurgitateRow);
        // Resize the number
        mNumToRegurgitate->SetXRay(false);

        level->GetItems()->push_back(mNumToRegurgitate);

        // Remove the number from the xRay
        xRay->DeleteItem(mNumToRegurgitate);

        // Check if game has been solved
        level->CheckSolve();

        //Reset values after regurgitation
        mNumToRegurgitate = nullptr;
        mRegurgitateCol = 0;
        mRegurgitateRow = 0;
    }
}
