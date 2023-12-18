/**
 * @file ContainerDeclaration.cpp
 * @author Devon FoxElster
 */

#include "pch.h"
#include "ContainerDeclaration.h"

using namespace std;

/// Constant value indicating the filepath to the images directory
std::wstring const FilePath = L"../resources/images/";

/**
 * Loads a ContainerDeclaration from an XML Node
 * @param node Node to load the data from
 */
void ContainerDeclaration::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);

    auto filename = node->GetAttribute(L"image");
    auto itemImage = wxImage(FilePath+filename, wxBITMAP_TYPE_ANY);
    mBackBitmap = make_unique<wxBitmap>(itemImage);

    filename = node->GetAttribute(L"front");
    itemImage = wxImage(FilePath+filename, wxBITMAP_TYPE_ANY);
    mFrontBitmap = make_unique<wxBitmap>(itemImage);
}
