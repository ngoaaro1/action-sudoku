/**
 * @file DeclarationVisitor.h
 * @author ethan
 *
 * Declaration visitor base class
 */

#ifndef PROJECT1_SUDOKULIB_DECLARATIONVISITOR_H
#define PROJECT1_SUDOKULIB_DECLARATIONVISITOR_H

// Forward references to all Declaration types
class BackgroundDeclaration;
class SingleImageDeclaration;
class ContainerDeclaration;
class NumberDeclaration;
class SpartyDeclaration;
class XRayDeclaration;


/**
 * Declaration visitor base class
 */
class DeclarationVisitor
{
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
     DeclarationVisitor() {}
public:
    virtual ~DeclarationVisitor() {}

    /**
     * Visit a BackgroundDeclaration object
     * @param backgroundDeclaration we are visiting
     */
    virtual void VisitBackgroundDeclaration(BackgroundDeclaration* backgroundDeclaration) {}

    /**
     * Visit a ContainerDeclaration object
     * @param containerDeclaration we are visiting
     */
    virtual void VisitContainerDeclaration(ContainerDeclaration* containerDeclaration) {}

    /**
     * Visit a NumberDeclaration object
     * @param numberDeclaration we are visiting
     */
    virtual void VisitNumberDeclaration(NumberDeclaration* numberDeclaration) {}

    /**
     * Visit a SingleImageDeclaration object
     * @param singleImageDeclaration we are visiting
     */
    virtual void VisitSingleImageDeclaration(SingleImageDeclaration* singleImageDeclaration) {}

    /**
     * Visit a SpartyDeclaration object
     * @param spartyDeclaration Declaration we are visiting
     */
    virtual void VisitSpartyDeclaration(SpartyDeclaration* spartyDeclaration) {}

    /**
     * Visit a XRayDeclaration object
     * @param xRayDeclaration we are visiting
     */
    virtual void VisitXRayDeclaration(XRayDeclaration* xRayDeclaration) {}

};

#endif //PROJECT1_SUDOKULIB_DECLARATIONVISITOR_H
