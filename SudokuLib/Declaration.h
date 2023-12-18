/**
 * @file Declaration.h
 * @author Devon FoxElster
 *
 * File containing the Declaration class
 */

#ifndef PROJECT1_SUDOKULIB_DECLARATION_H
#define PROJECT1_SUDOKULIB_DECLARATION_H

#include "DeclarationVisitor.h"
/**
 * Class designed to store the image and other relevant information about that image
 */
class Declaration
{
private:
    std::wstring mID;   ///< ID of the Declaration
    double mHeight; ///< Height of the Declaration image
    double mWidth;  ///< Width of the Declaration image

public:
    /**
     * Declaration Constructor
     */
    Declaration() {};

    virtual void XmlLoad(wxXmlNode *node);

    /**
     * Getter for the width.
     * @return Width of declaration.
     */
    double GetWidth() { return mWidth; }

    /**
     * Getter for the height.
     * @return Height of declaration.
     */
    double GetHeight() { return mHeight; }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    virtual void Accept(DeclarationVisitor* visitor) = 0;

};

#endif //PROJECT1_SUDOKULIB_DECLARATION_H
