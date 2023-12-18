/**
 * @file BackgroundDeclaration.h
 * @author Devon FoxElster
 *
 * Declaration Class handling the images for all Background objects
 */

#ifndef PROJECT1_SUDOKULIB_BACKGROUNDDECLARATION_H
#define PROJECT1_SUDOKULIB_BACKGROUNDDECLARATION_H

#include "SingleImageDeclaration.h"

/**
 * Class containing the information needed to draw a background
 */
class BackgroundDeclaration : public SingleImageDeclaration
{
private:

public:
    /**
     * BackgroundDeclaration Constructor
     */
    BackgroundDeclaration() : SingleImageDeclaration() {};

    void Accept(DeclarationVisitor* visitor) override;
};

#endif //PROJECT1_SUDOKULIB_BACKGROUNDDECLARATION_H
