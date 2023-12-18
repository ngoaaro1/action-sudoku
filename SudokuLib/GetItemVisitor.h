/**
 * @file GetItemVisitor.h
 * @author ethan & Aaron
 *
 * Contains the GetItemVisitor class
 */

#ifndef PROJECT1_SUDOKULIB_GETITEMVISITOR_H
#define PROJECT1_SUDOKULIB_GETITEMVISITOR_H

#include "ItemVisitor.h"

// Forward references
class Sparty;
class Xray;
class Container;
class Digit;

/**
 * Class to retrieve a item of a certain type from an item base class.
 */
class GetItemVisitor : public ItemVisitor
{
private:
    /// The Sparty object to be stored in the visitor.
    Sparty * mSparty = nullptr;

    /// The Xray object to be stored in the visitor.
    Xray * mXray = nullptr;

    /// The Container object to be stored in the visitor.
    Container * mContainer = nullptr;

    /// The Digit object to be stored in the visitor
    Digit * mDigit = nullptr;

public:
    /**
    * Visit a Sparty object
    * @param sparty Sparty we are visiting
    */
    void VisitSparty(Sparty * sparty) override {
        mSparty = sparty;
    }

    /**
    * Visit a Xray object
    * @param xray Xray we are visiting
    */
    void VisitXray(Xray * xray) override {
        mXray = xray;
    }

    /**
    * Visit a Container object
    * @param container Container we are visiting
    */
    void VisitContainer(Container* container) override {
        mContainer = container;
    }

    /**
    * Visit a Digit object
    * @param digit Digit we are visiting
    */
    void VisitDigit(Digit* digit) override {
        mDigit = digit;
    }

    /**
   * Get the Sparty object for the game
   * @returns mSparty
   */
    auto GetSparty() { return mSparty; }

    /**
    * Get the Xray object for the game
    * @returns mXray
    */
    auto GetXray() { return mXray; }

    /**
    * Get the Container object
    * @returns mContainer
    */
    auto GetContainer() { return mContainer; }

    /**
    * Get the Digit object
    * @returns mDigit
    */
    auto GetDigit() { return mDigit; }
};

#endif //PROJECT1_SUDOKULIB_GETITEMVISITOR_H
