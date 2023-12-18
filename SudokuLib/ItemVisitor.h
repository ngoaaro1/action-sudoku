/**
 * @file ItemVisitor.h
 * @author Aaron Ngo
 *
 * Item visitor base class.
 */

#ifndef PROJECT1_SUDOKULIB_ITEMVISITOR_H
#define PROJECT1_SUDOKULIB_ITEMVISITOR_H

#include "Digit.h"
#include "Given.h"
// Forward references to all item types
class SingleImageItem;
class Container;
class Sparty;
class Xray;

/**
 * Item visitor base class
 */
class ItemVisitor
{
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    ItemVisitor() {}
public:
    virtual ~ItemVisitor() {}

    /**
     * Visit a SingleImageItem object
     * @param singleImageItem we are visiting
     */
    virtual void VisitSingleImageItem(SingleImageItem* singleImageItem) {}

    /**
    * Visit a Container object
    * @param container Container we are visiting
    */
    virtual void VisitContainer(Container* container) {}

    /**
    * Visit a Xray object
    * @param xray Xray we are visiting
    */
    virtual void VisitXray(Xray* xray) {}

    /**
    * Visit a Sparty object
    * @param sparty Sparty we are visiting
    */
    virtual void VisitSparty(Sparty* sparty) {}

    /**
     * Visit a digit object.
     * @param digit The digit object we are visiting.
     */
    virtual void VisitDigit(Digit* digit) {}

    /**
     * Visit a given object.
     * @param given The given object we are visiting.
     */
    virtual void VisitGiven(Given* given) {}

};

#endif //PROJECT1_SUDOKULIB_ITEMVISITOR_H
