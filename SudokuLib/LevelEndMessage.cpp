/**
 * @file LevelEndMessage.cpp
 * @author Michael Plante
 */

#include "pch.h"
#include "LevelEndMessage.h"

/// Message to display on level failure.
const std::wstring LevelFailMessage = L"Incorrect!";

/// Message to display on level completion.
const std::wstring LevelSuccessMessage = L"Level Complete!";

/**
 * Constructor
 * The message that will be displayed (varies depending on if level has been won or lost)
 */
LevelEndMessage::LevelEndMessage()
{
    mMessage = L"";
}

/**
 * Make message status as failure
 */
void LevelEndMessage::SetFailureStatus()
{
    mMessage = LevelFailMessage;
}

/**
 * Make message status as success
 */
void LevelEndMessage::SetSuccessStatus()
{
    mMessage = LevelSuccessMessage;
}

/**
 * Draws an ending message onto the screen
 * Message will either be "Incorrect!" or "Level Completed!"
 * @param graphics The graphics context
 * @param width Width of the game background
 * @param height Height of the game background
 */
void LevelEndMessage::Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    //
    // Measuring text and drawing centered
    //
    wxFont bigFont(wxSize(0, 100),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(0, 160, 0));

    double wid, hit;
    graphics->GetTextExtent(mMessage, &wid, &hit);
    graphics->DrawText(mMessage, width/2 - wid/2, height/2 - hit/2);

}