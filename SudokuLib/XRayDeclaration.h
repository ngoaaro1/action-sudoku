/**
 * @file XRayDeclaration.h
 * @author Devon FoxElster
 *
 * Declaration Class handling the images for all Xray objects
 */

#ifndef PROJECT1_SUDOKULIB_XRAYDECLARATION_H
#define PROJECT1_SUDOKULIB_XRAYDECLARATION_H

#include "SingleImageDeclaration.h"

/**
 * Forward reference to the class SudokuGame in SudokuGame.cpp \ SudokuGame.h
 */
class SudokuGame;
/**
 * Class containing the information needed to draw the XRay class
 */
class XRayDeclaration : public SingleImageDeclaration
{
private:
    int mCapacity = 0;  ///< Stomach capacity for the XRay
public:
    /**
     * XRayDeclaration Constructor
     */
    XRayDeclaration() : SingleImageDeclaration() {}

    /**
     * Returns how many items the Xray object can hold.
     * @returns mCapacity
     */
    auto GetCapacity() { return mCapacity; }

    void XmlLoad(wxXmlNode *node) override;


    void Accept(DeclarationVisitor* visitor) override;
};

#endif //PROJECT1_SUDOKULIB_XRAYDECLARATION_H
