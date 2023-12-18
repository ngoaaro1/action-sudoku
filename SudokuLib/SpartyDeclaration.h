/**
 * @file SpartyDeclaration.h
 * @author Devon FoxElster
 *
 * Declaration Class handling the images for all Sparty objects
 */

#ifndef PROJECT1_SUDOKULIB_SPARTYDECLARATION_H
#define PROJECT1_SUDOKULIB_SPARTYDECLARATION_H

#include "Declaration.h"

/**
 * Forward reference to the SudokuGame class in SudokuGame.cpp / SudokuGame.h
 */
class SudokuGame;

/**
 * Class containing the necessary image information for the Sparty
 */
class SpartyDeclaration : public Declaration
{
private:
    /// Angle at which to pivot the head when headbutting
    double mHeadPivotAngle;
    /// X coordinate to pivot around when headbutting
    double mHeadPivotX;
    /// Y coordinate to pivot around when headbutting
    double mHeadPivotY;

    /// Angle at which to pivot the mouth when eating
    double mMouthPivotAngle;
    /// X coordinate to pivot around when eating
    double mMouthPivotX;
    /// Y coordinate to pivot around when eating
    double mMouthPivotY;

    /// Target X coordinate for eating
    double mTargetX;
    /// Target Y coordinate for eating
    double mTargetY;

    /// Which bitmap to draw first
    int mFront;
    /// Head bitmap
    std::shared_ptr<wxBitmap> mBitmap1;
    /// Mouth bitmap
    std::shared_ptr<wxBitmap> mBitmap2;

    /// Width of sparty
    double mWidth;
    /// Height of sparty
    double mHeight;

public:
    /**
     * SpartyDeclaration Constructor
     */
    SpartyDeclaration() : Declaration() {}

    /**
     * Get bitmap representing Sparty's head.
     * @returns mBitmap1
     */
    auto GetHeadBitmap() { return mBitmap1; }

    /**
     * Get bitmap representing Sparty's mouth.
     * @returns mBitmap2
     */
    auto GetMouthBitmap() { return mBitmap2; }

    /**
     * Get the integer which indicates whether the head or mouth should be drawn last.
     * @returns mFront
     */
    int GetFront() const { return mFront; }

    /**
     * Returns the TargetX variable
     * @return double TargetX
     */
    double GetTargetX() const { return mTargetX; }

    /**
     * Returns the TargetY variable
     * @return double TargetY
     */
    double GetTargetY() const { return mTargetY; }

    /**
     * Returns the Mouth Pivot X coordinate
     * @return double X coordinate
     */
    double GetMouthPivotX() const { return mMouthPivotX; }

    /**
     * Returns the Mouth Pivot Y coordinate
     * @return double Y coordinate
     */
    double GetMouthPivotY() const { return mMouthPivotY; }

    /**
     * Returns the Mouth Pivot angle
     * @return double angle for rotation
     */
    double GetMouthPivotAngle() const { return mMouthPivotAngle; }

    /**
     * Returns the width of the Sparty bitmap
     * @return double width
     */
    double GetSpartyWidth() const { return mWidth; }

    /**
     * Returns the height of the Sparty bitmap
     * @return double height
     */
    double GetSpartyHeight() const { return mHeight; }
    /**
     * Gets X-coordinate of head pivot location on Sparty image
     * @return Head pivot location on X
     */
    double GetHeadPivotX() const { return mHeadPivotX;}
    /**
     * Gets Y-coordinate of head pivot location on Sparty image
     * @return Head pivot location on Y
     */
    double GetHeadPivotY() const { return mHeadPivotY; }
    /**
     * Gets angle head pivots to during headbutt animation in radians
     * @return Angle head rotates to when headbutting
     */
    double GetHeadPivotAngle() const { return mHeadPivotAngle; }


    void XmlLoad(wxXmlNode *node) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitSpartyDeclaration(this); }
};

#endif //PROJECT1_SUDOKULIB_SPARTYDECLARATION_H
