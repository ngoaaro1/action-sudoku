/**
 * @file ContainerDeclaration.h
 * @author Devon FoxElster
 *
 * Declaration Class handling the images for all Container objects
 */

#ifndef PROJECT1_SUDOKULIB_CONTAINERDECLARATION_H
#define PROJECT1_SUDOKULIB_CONTAINERDECLARATION_H

#include "Declaration.h"

/**
 * Forward reference to the SudokuGame class in SudokuGame.cpp / SudokuGame.h
 */
class SudokuGame;

/**
 * Class containing the information needed to draw the Container class
 */
class ContainerDeclaration : public Declaration
{
private:
    std::shared_ptr<wxBitmap> mBackBitmap;  ///< Image bitmap to be displayed first
    std::shared_ptr<wxBitmap> mFrontBitmap; ///< Image bitmap to be displayed last

public:
    /**
     * ContainerDeclaration Constructor
     */
    ContainerDeclaration() : Declaration() {}

    void XmlLoad(wxXmlNode *node) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitContainerDeclaration(this); }

    /**
     * Gets a vector containing both bitmaps for the Container
     * @return Vector of Bitmaps
     */
    std::vector<std::shared_ptr<wxBitmap>> const GetBitmaps() { return {mBackBitmap, mFrontBitmap}; }
};

#endif //PROJECT1_SUDOKULIB_CONTAINERDECLARATION_H
