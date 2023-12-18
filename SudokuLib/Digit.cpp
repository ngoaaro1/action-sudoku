/**
 * @file Digit.cpp
 * @author hankm
 */

#include "pch.h"
#include "Digit.h"
#include "SudokuGame.h"
#include "GetDigitVisitor.h"
#include "GetDeclarationVisitor.h"
#include "NumberDeclaration.h"
#include "GetNumberDeclaration.h"

using namespace std;

/**
 * Constructor for digits.
 * @param level The level this belongs to.
 */
Digit::Digit(Level* level) : SingleImageItem(level)
{

}

/**
 * Accept an item visitor to visit this digit.
 * @param visitor The visitor to accept.
 */
void Digit::Accept(ItemVisitor* visitor)
{
    SingleImageItem::Accept(visitor);
    visitor->VisitDigit(this);
}

/**
 * Figure out the digit value.
 * @return The value this digit item is associated with.
 */
int Digit::GetValue()
{
    GetNumberDeclaration visitor;

    GetDeclaration()->Accept(&visitor);

    return visitor.GetDeclaration()->GetValue();
}
