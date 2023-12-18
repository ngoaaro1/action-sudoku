/**
 * @file Alert.cpp
 * @author hankm
 */

#include "pch.h"
#include "Alert.h"

/// Speed to move the text at.
const double AlertSpeed = 400.0;

/// Margin for text.
const double TextMargin = 10;

/// Border Padding to either side of an alert
const double BorderPadding = 50;

/// Offset to properly display the padding
const double BorderPaddingOffset = 25;

/// Message rescaling factor
const double Rescale = 2.0;

/// Arbitrary value that guarantees an alert is offscreen
const double TopLimit = -100.0;

/**
 * Constructor for the alert class.
 * @param message The message to be displayed.
 * @param height Height of the message to be displayed
 */
Alert::Alert(std::wstring message, int height)
{
    mMessage = message;
    mHeight = height;
}

/**
 * Draw in the alert.
 * @param graphics The graphics context to display on.
 * @param width The width of the screen in pixels.
 */
void Alert::Draw(std::shared_ptr<wxGraphicsContext> graphics, int width)
{
    wxFont font(wxSize(0, 28),
                       wxFONTFAMILY_SWISS,
                       wxFONTSTYLE_NORMAL,
                       wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, wxColour(255, 0, 0));

    double alertWidth, alertHeight;
    graphics->GetTextExtent(mMessage, &alertWidth, &alertHeight);

    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    wxPen borderPen(wxColour(0,0,0),5); // Black border pen of thickness 5
    graphics->SetPen(borderPen);
    graphics->DrawRectangle((width/Rescale) - (alertWidth/Rescale) - (TextMargin/Rescale) - BorderPaddingOffset,
                            mHeight,
                            alertWidth + TextMargin + BorderPadding,
                            alertHeight + TextMargin);


    graphics->DrawText(mMessage, (width/Rescale) - (alertWidth/Rescale), mHeight + (TextMargin/Rescale));
}

/**
 * Updates the height of the alert.
 * @param elapsed The amount of time elapsed.
 */
void Alert::Update(double elapsed)
{
    mHeight -= elapsed*AlertSpeed;
}

/**
 * Identifies whether the alert is off the screen and ready to be deleted.
 * @return True if alert is ready to be deleted, false otherwise.
 */
bool Alert::ReadyForDelete()
{
    if (mHeight < TopLimit)
    {
        return true;
    }
    return false;
}
