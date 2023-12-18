/**
 * @file LevelBeginMessage.cpp
 * @author Michael Plante
 */

#include "pch.h"
#include "LevelBeginMessage.h"

///Determine margin size for space width
const int WidMargin = 25;

///Margin for large text
const int HitLargeTextMargin = 10;

///Margin for small text
const double HitSmallTextMargin = 7.5;

///Eat control message
const std::wstring EatMessage = L"space: Eat";

///Regurgitate control message
const std::wstring RegurgitateMessage = L"0-8: Regurgitate";

///Headbutt key message
const std::wstring HeadbuttMessage = L"B: Headbutt";

/**
 * Draws the beginning message for a level.
 * @param graphics The graphics context to draw on
 * @param width The width of the game background
 * @param height The height of the game background
 */
void LevelBeginMessage::Draw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    std::wstring levelBeginMessage = L"Level ";
    //Create level indicator message to display
    levelBeginMessage.append(mLevelNum);
    levelBeginMessage.append(L" Begin");

    //Set fonts for pieces of text and get their heights
    wxFont bigFont(wxSize(0, 100),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(0, 170, 0));

    double widLarge, hitLarge;
    graphics->GetTextExtent(levelBeginMessage, &widLarge, &hitLarge);


    wxFont smallerFont(wxSize(0, 50),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(smallerFont, wxColour(0, 0, 0));

    double widSmallFirst, widSmallSecond, widSmallThird, hitSmallFirst, hitSmallSecond, hitSmallThird;
    graphics->GetTextExtent(EatMessage, &widSmallFirst, &hitSmallFirst);
    graphics->GetTextExtent(RegurgitateMessage, &widSmallSecond, &hitSmallSecond);
    graphics->GetTextExtent(HeadbuttMessage, &widSmallThird, &hitSmallThird);

    //Calculate height of box
    double boxHeight = hitLarge + hitSmallFirst + hitSmallSecond + hitSmallThird + (2*HitLargeTextMargin) + (3*HitSmallTextMargin);

    //
    // Draw a filled rectangle
    //
    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(*wxBLACK_PEN);
    graphics->DrawRectangle(width/2 - widLarge/2 - WidMargin,
                            height/2 - hitLarge - hitSmallFirst - (2*HitLargeTextMargin) - (HitSmallTextMargin/2),
                            widLarge + (2*WidMargin),
                            boxHeight);

    //Draw bigger message
    graphics->SetFont(bigFont, wxColour(0, 170, 0));
    graphics->DrawText(levelBeginMessage, width/2 - widLarge/2, height/2 - hitLarge - hitSmallFirst - HitLargeTextMargin - HitSmallTextMargin/2);

    //Draw smaller message
    graphics->SetFont(smallerFont, wxColour(0, 0, 0));
    graphics->DrawText(EatMessage, width/2 - widSmallFirst/2, height/2 - hitSmallFirst - HitSmallTextMargin/2);
    graphics->DrawText(RegurgitateMessage, width/2 - widSmallSecond/2, height/2 + HitSmallTextMargin/2);
    graphics->DrawText(HeadbuttMessage, width/2 - widSmallThird/2, height/2 + hitSmallSecond + HitSmallTextMargin/2 + HitSmallTextMargin);
}

