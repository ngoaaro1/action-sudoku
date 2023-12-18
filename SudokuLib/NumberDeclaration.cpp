/**
 * @file NumberDeclaration.cpp
 * @author Devon FoxElster
 */

#include "pch.h"
#include "NumberDeclaration.h"

using namespace std;

/// Constant value indicating the filepath to the images directory
std::wstring const FilePath = L"../resources/images/";

/**
 * Loads a NumberDeclaration from an XML Node
 * @param node Node to load date from
 */
void NumberDeclaration::XmlLoad(wxXmlNode *node)
{
    SingleImageDeclaration::XmlLoad(node);
    node->GetAttribute(L"value").ToInt(&mValue);
}

/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void NumberDeclaration::Accept(DeclarationVisitor* visitor)
{
    SingleImageDeclaration::Accept(visitor);
    visitor->VisitNumberDeclaration(this);
}