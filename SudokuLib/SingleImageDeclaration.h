/**
 * @file SingleImageDeclaration.h
 * @author hankm
 *
 * Declaration Class handling the images for all Single Image Item objects
 */

#ifndef PROJECT1_SUDOKULIB_SINGLEIMAGEDECLARATION_H
#define PROJECT1_SUDOKULIB_SINGLEIMAGEDECLARATION_H

#include "Declaration.h"

/**
 * Intermediate class for all Declarations that
 * only require a single Bitmap for drawing
 */
class SingleImageDeclaration : public Declaration
{
private:
    std::shared_ptr<wxBitmap> mBitmap = nullptr;  ///< Image bitmap for the declaration.

public:
    /**
     * SingleImageDeclaration Constructor
     */
    SingleImageDeclaration() : Declaration() {}
    virtual void XmlLoad(wxXmlNode* node) override;

    /**
     * Simple getter of the Bitmap for Image Drawing purposes
     * @return Shared Vector of a Bitmap
     */
    std::shared_ptr<wxBitmap> GetBitmap() { return mBitmap; };

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitSingleImageDeclaration(this); }

};

#endif //PROJECT1_SUDOKULIB_SINGLEIMAGEDECLARATION_H
