/**
 * @file GetNumberDeclaration.h
 * @author hankm
 *
 * A visitor class that finds a number declaration.
 */

#ifndef PROJECT1_SUDOKULIB_GETNUMBERDECLARATION_H
#define PROJECT1_SUDOKULIB_GETNUMBERDECLARATION_H

#include "DeclarationVisitor.h"

/**
 * A visitor class that finds a number declaration.
 */
class GetNumberDeclaration : public DeclarationVisitor
{
private:
    /// The found number declaration.
    NumberDeclaration* mNumberDeclaration = nullptr;

public:
    /**
     * Visit a number declaration.
     * @param declaration The declaration to visit.
     */
    void VisitNumberDeclaration(NumberDeclaration* declaration) override { mNumberDeclaration = declaration; }

    /**
     * Getter for the found number declaration.
     * @return The number declaration.
     */
    NumberDeclaration* GetDeclaration() { return mNumberDeclaration; };

};

#endif //PROJECT1_SUDOKULIB_GETNUMBERDECLARATION_H
