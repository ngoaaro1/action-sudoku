/**
 * @file NumberEvaluator.h
 * @author hankm
 *
 * Visitor class checks if a item is a number.
 */

#ifndef PROJECT1_SUDOKULIB_NUMBEREVALUATOR_H
#define PROJECT1_SUDOKULIB_NUMBEREVALUATOR_H

#include "ItemVisitor.h"
#include "Given.h"

/**
 * Visitor class checks if a item is a number.
 */
class NumberEvaluator : public ItemVisitor
{
private:
    bool mFoundNumber = false; ///< Boolean checking if the item is a number

public:
    /**
     * Getter for if a number has been found.
     * @return True if a number, false otherwise.
     */
    bool GetFoundNumber() { return mFoundNumber; }

    /**
     * Visit a digit, means we have found a number.
     * @param digit The digit to visit.
     */
    void VisitDigit(Digit* digit) override { mFoundNumber = true; }

    /**
     * Visit a given, means we have found a number.
     * @param given The given to visit.
     */
    void VisitGiven(Given* given) override { mFoundNumber = true; }
};

#endif //PROJECT1_SUDOKULIB_NUMBEREVALUATOR_H
