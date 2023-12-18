/**
 * @file GetDigitVisitor.cpp
 * @author hankm
 */

#include "pch.h"
#include "GetDigitVisitor.h"

/**
 * Visit a digit and see if it matches the value.
 * @param digit The digit to check.
 */
void GetDigitVisitor::VisitDigit(Digit *digit)
{
    if (digit->GetValue() == mValueToSearch)
    {
        mDigit = digit;
    }
}
