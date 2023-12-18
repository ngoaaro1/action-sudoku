/**
 * @file Sparty.h
 * @author Devon FoxElster
 *
 * File containing the Sparty Class
 */



#ifndef PROJECT1_SUDOKULIB_SPARTY_H
#define PROJECT1_SUDOKULIB_SPARTY_H

#include "Item.h"
#include "SudokuGame.h"

class ItemVisitor;

/**
 * Sparty class to control the Sparty head used to play the Sudoku game
 */
class Sparty : public Item
{
private:
    double mSpeedX = 0; ///< Horizontal movement speed of Sparty
    double mSpeedY = 0; ///< Vertical movement speed of Sparty

    double mDestinationX;   ///< X coordinate the Sparty moves toward
    double mDestinationY;   ///< Y coordinate the Sparty moves toward

    ///Members to store information about an animation/action state Sparty is currently in
    bool mHeadbutting = false; ///< Whether Sparty is in a headbutting state
    bool mEating = false; ///< Whether Sparty is in an eating state
    bool mRegurgitating = false; ///< Whether Sparty is in a regurgitating state

    ///Members to hold information about a rotation that Sparty is undergoing
    bool mRotatingClockwise = true; ///< Determines if rotation is clockwise
    double mCurrentAngle = 0; ///< Amount rotation has occurred

    ///Members to hold information necessary to perform a regurgitation
    std::shared_ptr<Item> mNumToRegurgitate; ///< Holds the item that is going to be regurgitated
    double mRegurgitateCol; ///< Holds the column location of a regurgitation
    double mRegurgitateRow; ///< Holds the row location of a regurgitation

    void PerformEat();

    void PerformHeadbutt();

    void PerformRegurgitate();

    void CalculateAngle(double elapsed);

    bool EatHitTest(Item * item);

    bool HeadbuttHitTest(Item * item);

public:
    Sparty(Level* level);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void OnLeftDown(double x, double y, int tileWidth, int tileHeight);

    void Update(double elapsed);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override;

    /**
     * Sets the Sparty's speed to the given values
     * @param speedX New horizontal speed
     * @param speedY New vertical speed
     */
    void ChangeSpeed(double speedX, double speedY) {mSpeedX = speedX; mSpeedY = speedY; }

    /**
     * Returns the X Speed of sparty
     * @return mSpeedX
     */
    double GetSpeedX() {return mSpeedX;}

    /**
     * Returns the Y speed of sparty
     * @return mSpeedY
     */
    double GetSpeedY() {return mSpeedY;}


    /**
     * Sets an end destination for the Sparty
     * @param destinationX X coordinate to move toward
     * @param destinationY Y coordinate to move toward
     */
    void SetDestination(double destinationX, double destinationY) { mDestinationX = destinationX; mDestinationY = destinationY; }

    void Headbutt();

    void Regurgitate(int number);

    void Eat();

};

#endif //PROJECT1_SUDOKULIB_SPARTY_H
