/**
 * @file XRayDeclaration.cpp
 * @author Devon FoxElster
 */

#include "pch.h"
#include "XRayDeclaration.h"

using namespace std;

/**
 * Loads XRay Declaration data from a node
 * @param node Node to load a declaration from
 */
void XRayDeclaration::XmlLoad(wxXmlNode *node)
{
    SingleImageDeclaration::XmlLoad(node);
    node->GetAttribute(L"capacity", L"0").ToInt(&mCapacity);
}

/**
 * Accept a visitor
 * @param visitor The visitor we accept
 */
void XRayDeclaration::Accept(DeclarationVisitor *visitor)
{
    SingleImageDeclaration::Accept(visitor);
    visitor->VisitXRayDeclaration(this);
}