/**
 * @file SingleImageDeclaration.cpp
 * @author hankm
 */

#include "pch.h"
#include <memory>
#include "SingleImageDeclaration.h"
#include "Declaration.h"

using namespace::std;

/// Constant value indicating the filepath to the images directory
std::wstring const FilePath = L"../resources/images/";

/**
 * Loads relevant XML attributes into this object.
 * @param node The node to extract values from.
 */
void SingleImageDeclaration::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);

    auto filename = node->GetAttribute(L"image");
    auto itemImage = wxImage(FilePath+filename, wxBITMAP_TYPE_ANY);
    mBitmap = make_shared<wxBitmap>(itemImage);
}
