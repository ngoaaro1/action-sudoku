/**
 * @file GetDeclarationVisitor.h
 * @author ethan
 *
 * Contains the GetDeclarationVisitor class
 */

#ifndef PROJECT1_SUDOKULIB_GETDECLARATIONVISITOR_H
#define PROJECT1_SUDOKULIB_GETDECLARATIONVISITOR_H

#include "DeclarationVisitor.h"
#include "SingleImageDeclaration.h"

// Forward references
class SingleImageDeclaration;
class ContainerDeclaration;
class SpartyDeclaration;
class NumberDeclaration;

/**
 * Class to retrieve a declaration of a certain type from a declaration base class.
 */
class GetDeclarationVisitor: public DeclarationVisitor
{
private:
    /// The SingleImageDeclaration to be stored in the visitor.
    SingleImageDeclaration *mSingleImageDeclaration = nullptr;

    /// The ContainerDeclaration to be stored in the visitor.
    ContainerDeclaration *mContainerDeclaration = nullptr;

    /// The SpartyDeclaration to be stored in the visitor.
    SpartyDeclaration *mSpartyDeclaration = nullptr;

    /// The NumberDeclaration to be stored in the visitor.
    NumberDeclaration *mNumberDeclaration = nullptr;

    /// The XrayDeclaration to be stored in the visitor
    XRayDeclaration *mXRayDeclaration = nullptr;

public:
    /**
     * Getter for the SingeImageDeclaration.
     * @return mSingleImageDeclaration
     */
    SingleImageDeclaration * GetSingleImageDeclaration() const { return mSingleImageDeclaration; }

    /**
     * Getter for the ContainerDeclaration.
     * @return mContainerDeclaration
     */
    ContainerDeclaration * GetContainerDeclaration() const { return mContainerDeclaration; }

    /**
     * Getter for the SpartyDeclaration.
     * @return mSpartyDeclaration
     */
    SpartyDeclaration * GetSpartyDeclaration() const { return mSpartyDeclaration; }

    /**
     * Getter for the SpartyDeclaration.
     * @return mSpartyDeclaration
     */
    XRayDeclaration * GetXRayDeclaration() const { return mXRayDeclaration; }

    /**
     * Getter for the NumberDeclaration
     * @return mNumberDeclaration
     */
    NumberDeclaration* GetNumberDeclaration() const { return mNumberDeclaration; }

    /**
    * Visit a SingleImageDeclaration object
    * @param declaration Declaration we are visiting
    */
    void VisitSingleImageDeclaration(SingleImageDeclaration * declaration) override { mSingleImageDeclaration = declaration; }

    /**
    * Visit a ContainerDeclaration object
    * @param declaration Declaration we are visiting
    */
    void VisitContainerDeclaration(ContainerDeclaration * declaration) override { mContainerDeclaration = declaration; }

    /**
    * Visit a SpartyDeclaration object
    * @param declaration Declaration we are visiting
    */
    void VisitSpartyDeclaration(SpartyDeclaration * declaration) override { mSpartyDeclaration = declaration; }

    /**
     * Visit a DigitDeclaration object
     * @param declaration Declaration we are visiting
     */
    void VisitNumberDeclaration(NumberDeclaration *declaration) override { mNumberDeclaration = declaration; }

    /**
    * Visit a XRayDeclaration object
    * @param declaration Declaration we are visiting
    */
    void VisitXRayDeclaration(XRayDeclaration * declaration) override { mXRayDeclaration = declaration; }

};

#endif //PROJECT1_SUDOKULIB_GETDECLARATIONVISITOR_H
