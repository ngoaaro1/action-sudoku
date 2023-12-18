/**
 * @file GetDigitVisitor.h
 * @author hankm
 *
 * Contains the GetDigitVisitor class
 */

#ifndef PROJECT1_SUDOKULIB_GETDIGITVISITOR_H
#define PROJECT1_SUDOKULIB_GETDIGITVISITOR_H

#include "ItemVisitor.h"
#include "Digit.h"

/**
 * Visitor class to retrieve the value of Digit objects
 */
class GetDigitVisitor : public ItemVisitor
{
private:
    /// The value of the digit to find.
    int mValueToSearch;

    /// The found digit pointer.
    Digit* mDigit = nullptr;

public:
    /**
     * Constructor.
     * @param searchValue the value to search for.
     */
    GetDigitVisitor(int searchValue) { mValueToSearch = searchValue; }

    /**
     * Reset the found to nullptr.
     */
    void Reset() { mDigit = nullptr; }

    /**
     * Getter for the found digit.
     * @return The found digit pointer.
     */
    Digit* GetDigit() { return mDigit; }

    void VisitDigit(Digit* digit) override;

};

#endif //PROJECT1_SUDOKULIB_GETDIGITVISITOR_H
