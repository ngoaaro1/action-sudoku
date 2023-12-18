/**
 * @file SpartyDeclaration.cpp
 * @author Devon FoxElster
 */

#include "pch.h"
#include "SpartyDeclaration.h"

using namespace std;

/// Constant value indicating the filepath to the images directory
std::wstring const FilePath = L"../resources/images/";

/**
 * Loads a Sparty Declaration from an XML Node
 * @param node Node to load the declaration from
 */
void SpartyDeclaration::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);
    node->GetAttribute(L"width").ToDouble(&mWidth);
    node->GetAttribute(L"height").ToDouble(&mHeight);
    node->GetAttribute(L"front", L"0").ToInt(&mFront);
    node->GetAttribute(L"head-pivot-angle").ToDouble(&mHeadPivotAngle);
    node->GetAttribute(L"head-pivot-x").ToDouble(&mHeadPivotX);
    node->GetAttribute(L"head-pivot-y").ToDouble(&mHeadPivotY);
    node->GetAttribute(L"mouth-pivot-angle").ToDouble(&mMouthPivotAngle);
    node->GetAttribute(L"mouth-pivot-x").ToDouble(&mMouthPivotX);
    node->GetAttribute(L"mouth-pivot-y").ToDouble(&mMouthPivotY);
    node->GetAttribute(L"target-x").ToDouble(&mTargetX);
    node->GetAttribute(L"target-y").ToDouble(&mTargetY);

    auto filename = node->GetAttribute(L"image1");
    auto itemImage = wxImage(FilePath+filename, wxBITMAP_TYPE_ANY);
    mBitmap1 = make_unique<wxBitmap>(itemImage);

    filename = node->GetAttribute(L"image2");
    itemImage = wxImage(FilePath+filename, wxBITMAP_TYPE_ANY);
    mBitmap2 = make_unique<wxBitmap>(itemImage);
}
