/**
 * @file NumberDeclaration.h
 * @author Devon FoxElster
 *
 * Declaration Class handling the images for all Number objects
 */

#ifndef PROJECT1_SUDOKULIB_NUMBERDECLARATION_H
#define PROJECT1_SUDOKULIB_NUMBERDECLARATION_H

#include "SingleImageDeclaration.h"

/**
 * Class containing the information needed to draw the Number class
 */
class NumberDeclaration : public SingleImageDeclaration
{
private:
    int mValue; ///< Value of the number

public:
    /**
     * NumberDeclaration Constructor
     */
    NumberDeclaration() : SingleImageDeclaration() {}

    void XmlLoad(wxXmlNode *node) override;

    void Accept(DeclarationVisitor* visitor) override;

    /**
     * Getter for the mValue variable
     * @return mValue
     */
    int GetValue() { return mValue; }
};

#endif //PROJECT1_SUDOKULIB_NUMBERDECLARATION_H
