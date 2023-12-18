/**
 * @file SudokuGame.cpp
 * @author hankm
 */

#include "pch.h"
#include <wx/graphics.h>
#include "SudokuGame.h"
#include "ids.h"
#include "Digit.h"
#include "Given.h"
#include "Xray.h"
#include "Background.h"
#include "Declaration.h"
#include "Item.h"
#include "SpartyDeclaration.h"
#include "XRayDeclaration.h"
#include "NumberDeclaration.h"
#include "ContainerDeclaration.h"
#include "BackgroundDeclaration.h"
#include "GetItemVisitor.h"
#include "Sparty.h"
#include <cmath>
#include <iostream>
#include "GetDeclarationVisitor.h"

using namespace std;

/**
 * Sudoku Game Constructor
 */
SudokuGame::SudokuGame() : mLevel(IDM_LEVEL_LEVEL1)
{

}

/**
 * Activated when window is redrawn, this handles
 * redrawing anything managed by Sudoku Game.
 * @param graphics The device context.
 * @param height Total height of the window
 * @param width Total width of the window
 */
void SudokuGame::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{

    // Determine the size of the playing area in pixels
    // This is up to you...
    int pixelWidth = mLevel.GetPixelWidth();
    int pixelHeight = mLevel.GetPixelHeight();

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    // Draw Level
    mLevel.Draw(graphics);

    // Include Drawing of the Items here
    graphics->PopState();
}

/**
 * Sets the level of the game.
 * @param level The level to set to, see ids.h.
 */
void SudokuGame::SetLevel(int level)
{
    mLevel.SetLevel(level);
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */

void SudokuGame::Update(double elapsed)
{
    mLevel.Update(elapsed);
}

/**
 * Activated on left click handle game control.
 * @param x X coordinate for the event.
 * @param y Y coordinate for the event.
 */
void SudokuGame::OnLeftDown(double x, double y)
{
    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;
    mLevel.OnLeftDown(oX, oY);
}
