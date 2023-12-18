/**
 * @file BackgroundDeclaration.cpp
 * @author Devon FoxElster
 */

#include "pch.h"
#include "BackgroundDeclaration.h"

/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void BackgroundDeclaration::Accept(DeclarationVisitor* visitor) {
    SingleImageDeclaration::Accept(visitor);
    visitor->VisitBackgroundDeclaration(this);
}