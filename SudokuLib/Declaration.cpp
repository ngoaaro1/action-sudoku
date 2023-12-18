/**
 * @file Declaration.cpp
 * @author Devon FoxElster
 */

#include "pch.h"
#include "Declaration.h"

using namespace std;

/**
 * Loads a Declaration from an XML Node
 * @param node Node to load from
 */
void Declaration::XmlLoad(wxXmlNode *node)
{
    mID = node->GetAttribute(L"id", L"");
    node->GetAttribute(L"height", L"0").ToDouble(&mHeight);
    node->GetAttribute(L"width", L"0").ToDouble(&mWidth);
}