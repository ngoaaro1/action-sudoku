/**
 * @file Given.cpp
 * @author hankm
 */

#include "pch.h"
#include "Given.h"
#include "Item.h"
#include "ItemVisitor.h"
#include "GetNumberDeclaration.h"
#include "NumberDeclaration.h"

/**
 * Visitor accept function for Given objects
 * @param visitor Visitor class to look at the Given object
 */
void Given::Accept(ItemVisitor *visitor)
{
    SingleImageItem::Accept(visitor);
    visitor->VisitGiven(this);
}

/**
 * Figure out the given value.
 * @return The value this given item is associated with.
 */
int Given::GetValue()
{
    GetNumberDeclaration visitor;

    GetDeclaration()->Accept(&visitor);

    return visitor.GetDeclaration()->GetValue();
}
