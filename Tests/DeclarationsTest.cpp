/**
 * @file DeclarationsTest.cpp
 * @author Devon FoxElster
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <SudokuGame.h>
#include <Declaration.h>
#include <DeclarationVisitor.h>
#include <wx/filename.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

// Constant value indicating the filepath to the images directory
std::wstring const FilePath = L"../resources/images/";

/**
 * A derived class from Declaration to use for tests
 */
class DeclarationsMock : public Declaration
{
private:
public:
    DeclarationsMock() : Declaration() {}
    void Accept(DeclarationVisitor *) override {}

    std::wstring mID;
    double mHeight;
    double mWidth;
    std::unique_ptr<wxBitmap> mBackBitmap;
    std::unique_ptr<wxBitmap> mFrontBitmap;
    int mValue;
    std::shared_ptr<wxBitmap> mBitmap;
    double mHeadPivotAngle;
    double mHeadPivotX;
    double mHeadPivotY;
    double mMouthPivotAngle;
    double mMouthPivotX;
    double mMouthPivotY;
    double mTargetX;
    double mTargetY;
    int mFront;
    std::unique_ptr<wxBitmap> mBitmap1;
    std::unique_ptr<wxBitmap> mBitmap2;
    int mCapacity;

    void XmlLoad(wxXmlNode *node)
    {
        mID = node->GetAttribute(L"id", L"");
        node->GetAttribute(L"height", L"0").ToDouble(&mHeight);
        node->GetAttribute(L"width", L"0").ToDouble(&mWidth);
    }

    // General Number Load Function
    void NumberXmlLoad(wxXmlNode *node)
    {
        SingleImageXmlLoad(node);
        node->GetAttribute(L"value").ToInt(&mValue);
    }

    // Container Load Function
    void ContainerXmlLoad(wxXmlNode *node)
    {
        XmlLoad(node);

        auto filename = node->GetAttribute(L"image");
        auto itemImage = wxImage(FilePath+filename, wxBITMAP_TYPE_ANY);
        mBackBitmap = make_unique<wxBitmap>(itemImage);

        filename = node->GetAttribute(L"front");
        itemImage = wxImage(FilePath+filename, wxBITMAP_TYPE_ANY);
        mFrontBitmap = make_unique<wxBitmap>(itemImage);
    }

    // Image Load Function
    void SingleImageXmlLoad(wxXmlNode *node)
    {
        XmlLoad(node);

        auto filename = node->GetAttribute(L"image");
        auto itemImage = wxImage(FilePath+filename, wxBITMAP_TYPE_ANY);
        mBitmap = make_shared<wxBitmap>(itemImage);
    }

    // Sparty Load Function
    void SpartyXmlLoad(wxXmlNode *node)
    {
        XmlLoad(node);
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

    // XRay Load Function
    void XRayXmlLoad(wxXmlNode *node)
    {
        SingleImageXmlLoad(node);
        node->GetAttribute(L"capacity", L"0").ToInt(&mCapacity);

        auto filename = node->GetAttribute(L"image");
        auto itemImage = wxImage(FilePath+filename, wxBITMAP_TYPE_ANY);
        mBitmap = make_unique<wxBitmap>(itemImage);
    }

};


TEST(DeclarationsTest, NumberDeclarationLoad)
{
    wxXmlNode mGivenNode = wxXmlNode(wxXML_ELEMENT_NODE, L"given");
    wxXmlNode mDigitNode = wxXmlNode(wxXML_ELEMENT_NODE, L"digit");

    mGivenNode.AddAttribute(L"id", L"i225");
    mGivenNode.AddAttribute(L"width", L"48");
    mGivenNode.AddAttribute(L"height", L"48");
    mGivenNode.AddAttribute(L"value", L"1");
    mGivenNode.AddAttribute(L"image",L"1r.png");

    mDigitNode.AddAttribute(L"id", L"i228");
    mDigitNode.AddAttribute(L"width", L"48");
    mDigitNode.AddAttribute(L"height", L"48");
    mDigitNode.AddAttribute(L"value", L"3");
    mDigitNode.AddAttribute(L"image",L"3b.png");

    DeclarationsMock declaration1;
    DeclarationsMock declaration2;
    declaration1.NumberXmlLoad(&mGivenNode);
    declaration2.NumberXmlLoad(&mDigitNode);

    // Asserts that all values of the Declaration are what we expect
    // after the loading
    ASSERT_TRUE(declaration1.mValue == 1);
    ASSERT_TRUE(declaration1.mID == L"i225");
    ASSERT_TRUE(declaration1.mWidth == 48.0);
    ASSERT_TRUE(declaration1.mHeight == 48.0);
    ASSERT_TRUE(declaration1.mBitmap != nullptr);

    // Asserts that all values of the Declaration are what we expect
    // after the loading
    ASSERT_TRUE(declaration2.mValue == 3);
    ASSERT_TRUE(declaration2.mID == L"i228");
    ASSERT_TRUE(declaration2.mWidth == 48.0);
    ASSERT_TRUE(declaration2.mHeight == 48.0);
    ASSERT_TRUE(declaration2.mBitmap != nullptr);
}

TEST(DeclarationsTest, XRayDeclarationLoad)
{
    wxXmlNode mXRayNode = wxXmlNode(wxXML_ELEMENT_NODE, L"xray");

    DeclarationsMock declaration;

    mXRayNode.AddAttribute(L"id", L"i244");
    mXRayNode.AddAttribute(L"width", L"144");
    mXRayNode.AddAttribute(L"height", L"144");
    mXRayNode.AddAttribute(L"capacity", L"7");
    mXRayNode.AddAttribute(L"image",L"xray.png");

    declaration.XRayXmlLoad(&mXRayNode);
    // Asserts that all values of the Declaration are what we expect
    // after the loading
    ASSERT_TRUE(declaration.mCapacity == 7);
    ASSERT_TRUE(declaration.mID == L"i244");
    ASSERT_TRUE(declaration.mWidth == 144.0);
    ASSERT_TRUE(declaration.mHeight == 144.0);
    ASSERT_TRUE(declaration.mBitmap != nullptr);
}

TEST(DeclarationsTest, BackgroundDeclarationLoad)
{
    wxXmlNode mBackgroundNode = wxXmlNode(wxXML_ELEMENT_NODE, L"background");
    wxXmlNode mContainerNode = wxXmlNode(wxXML_ELEMENT_NODE, L"container");
    wxXmlNode mSpartyNode = wxXmlNode(wxXML_ELEMENT_NODE, L"sparty");

    DeclarationsMock declaration;

    mBackgroundNode.AddAttribute(L"id", L"i245");
    mBackgroundNode.AddAttribute(L"width", L"528");
    mBackgroundNode.AddAttribute(L"height", L"528");
    mBackgroundNode.AddAttribute(L"image",L"sudoku.png");

    declaration.SingleImageXmlLoad(&mBackgroundNode);

    // Asserts that all values of the Declaration are what we expect
    // after the loading
    ASSERT_TRUE(declaration.mID == L"i245");
    ASSERT_TRUE(declaration.mWidth == 528.0);
    ASSERT_TRUE(declaration.mHeight == 528.0);
    ASSERT_TRUE(declaration.mBitmap != nullptr);
}

TEST(DeclarationsTest, ContainerDeclarationLoad)
{
    wxXmlNode mContainerNode = wxXmlNode(wxXML_ELEMENT_NODE, L"container");

    DeclarationsMock declaration;

    mContainerNode.AddAttribute(L"id", L"i247");
    mContainerNode.AddAttribute(L"width", L"204");
    mContainerNode.AddAttribute(L"height", L"176");
    mContainerNode.AddAttribute(L"image",L"pumpkin.png");
    mContainerNode.AddAttribute(L"front", L"pumpkin-front.png");

    declaration.ContainerXmlLoad(&mContainerNode);

    // Asserts that all values of the Declaration are what we expect
    // after the loading
    ASSERT_TRUE(declaration.mID == L"i247");
    ASSERT_TRUE(declaration.mWidth == 204.0);
    ASSERT_TRUE(declaration.mHeight == 176.0);
    ASSERT_TRUE(declaration.mBackBitmap != nullptr);
    ASSERT_TRUE(declaration.mFrontBitmap != nullptr);
}

TEST(DeclarationsTest, Sparty)
{
    wxXmlNode mSpartyNode = wxXmlNode(wxXML_ELEMENT_NODE, L"sparty");

    DeclarationsMock declaration;

    mSpartyNode.AddAttribute(L"id", L"i250");
    mSpartyNode.AddAttribute(L"width", L"96");
    mSpartyNode.AddAttribute(L"height", L"96");
    mSpartyNode.AddAttribute(L"image1",L"sparty-3.png");
    mSpartyNode.AddAttribute(L"image2", L"sparty-4.png");
    mSpartyNode.AddAttribute(L"front", L"1");
    mSpartyNode.AddAttribute(L"head-pivot-angle", L"1.5");
    mSpartyNode.AddAttribute(L"head-pivot-x", L"40");
    mSpartyNode.AddAttribute(L"head-pivot-y", L"86");
    mSpartyNode.AddAttribute(L"mouth-pivot-angle", L"0.5");
    mSpartyNode.AddAttribute(L"mouth-pivot-x", L"30");
    mSpartyNode.AddAttribute(L"mouth-pivot-y", L"65");
    mSpartyNode.AddAttribute(L"target-x", L"72");
    mSpartyNode.AddAttribute(L"target-y", L"24");

    declaration.SpartyXmlLoad(&mSpartyNode);

    // Asserts that all values of the Declaration are what we expect
    // after the loading
    ASSERT_TRUE(declaration.mID == L"i250");
    ASSERT_TRUE(declaration.mWidth == 96.0);
    ASSERT_TRUE(declaration.mHeight == 96.0);
    ASSERT_TRUE(declaration.mBitmap1 != nullptr);
    ASSERT_TRUE(declaration.mBitmap2 != nullptr);
    ASSERT_TRUE(declaration.mTargetX == 72.0);
    ASSERT_TRUE(declaration.mTargetY == 24.0);
    ASSERT_TRUE(declaration.mMouthPivotAngle == 0.5);
    ASSERT_TRUE(declaration.mMouthPivotX == 30.0);
    ASSERT_TRUE(declaration.mMouthPivotY == 65.0);
    ASSERT_TRUE(declaration.mHeadPivotAngle == 1.5);
    ASSERT_TRUE(declaration.mHeadPivotX == 40.0);
    ASSERT_TRUE(declaration.mHeadPivotY == 86.0);

}
