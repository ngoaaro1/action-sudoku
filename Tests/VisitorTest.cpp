/**
 * @file SudokuGameTest.cpp
 * @author Devon FoxElster
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <SudokuGame.h>
#include <wx/filename.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <ids.h>
#include <ItemVisitor.h>
#include <DeclarationVisitor.h>

using namespace std;

/**
 * A derived class from ItemVisitor to use for tests
 */
class TestItemVisitor : public ItemVisitor
{
public:
    virtual void VisitSingleImageItem(SingleImageItem* singleImageItem) {mNumSingleImageItems++;}
    virtual void VisitContainer(Container* container) {mNumContainers++;}
    virtual void VisitXray(Xray* xray) {mNumXRay++;}
    virtual void VisitSparty(Sparty* sparty) {mNumSparty++;}
    virtual void VisitDigit(Digit* digit) {mNumDigit++;}
    virtual void VisitGiven(Given* given) {mNumGiven++;}

    int mNumContainers = 0;
    int mNumXRay = 0;
    int mNumDigit = 0;
    int mNumGiven = 0;
    int mNumSparty = 0;
    int mNumSingleImageItems = 0;
};

/**
 * A derived class from DeclarationVisitor to use for tests
 */
class TestDeclarationVisitor : public DeclarationVisitor
{
public:
    virtual void VisitBackgroundDeclaration(BackgroundDeclaration* backgroundDeclaration) {mNumBackground++;}
    virtual void VisitContainerDeclaration(ContainerDeclaration* containerDeclaration) {mNumContainer++;}
    virtual void VisitNumberDeclaration(NumberDeclaration* numberDeclaration) {mNumNumber++;}
    virtual void VisitSingleImageDeclaration(SingleImageDeclaration* singleImageDeclaration) {mNumSingleImage++;}
    virtual void VisitSpartyDeclaration(SpartyDeclaration* spartyDeclaration) {mNumSparty++;}
    virtual void VisitXRayDeclaration(XRayDeclaration* xRayDeclaration) {mNumXRay++;}

    int mNumBackground = 0;
    int mNumContainer = 0;
    int mNumNumber = 0;
    int mNumSingleImage = 0;
    int mNumSparty = 0;
    int mNumXRay = 0;
};

TEST(SudokuGameTest, ItemVisitor)
{
    //Create a level object and load level 2 into that object
    Level level(IDM_LEVEL_LEVEL1);
    //Create visitor of mock class type
    TestItemVisitor visitor;

    //Add visitor of mock class type to the level
    level.Accept(&visitor);

    //Ensure counts are correct for level 2
    ASSERT_EQ(28, visitor.mNumGiven);
    ASSERT_EQ(53, visitor.mNumDigit);
    ASSERT_EQ(1, visitor.mNumContainers);
    ASSERT_EQ(1, visitor.mNumXRay);
    ASSERT_EQ(0, visitor.mNumSparty); //<We expect this to equal 0 because Sparty is never added to item list
    ASSERT_EQ(82, visitor.mNumSingleImageItems);

    //Load level 1 into level
    level.SetLevel(IDM_LEVEL_LEVEL2);
    //Create visitor for level 2
    TestItemVisitor visitorTwo;

    level.Accept(&visitorTwo);
    //Ensure counts are correct for level 2
    ASSERT_EQ(34, visitorTwo.mNumGiven);
    ASSERT_EQ(31, visitorTwo.mNumDigit);
    ASSERT_EQ(3, visitorTwo.mNumContainers);
    ASSERT_EQ(1, visitorTwo.mNumXRay);
    ASSERT_EQ(0, visitorTwo.mNumSparty); //<We expect this to equal 0 because Sparty is never added to item list
    ASSERT_EQ(67, visitorTwo.mNumSingleImageItems);
}

TEST(SudokuGameTest, DeclarationVisitor)
{
    //Test level 1 counts
    Level level(IDM_LEVEL_LEVEL1);

    TestDeclarationVisitor visitor;


    for (auto item : *level.GetItems())
    {
        item->GetDeclaration()->Accept(&visitor);
    }

    ASSERT_EQ(1, visitor.mNumBackground);
    ASSERT_EQ(0, visitor.mNumContainer);
    ASSERT_EQ(81, visitor.mNumNumber); //< Checks the number of items storing a declaration
    ASSERT_EQ(83, visitor.mNumSingleImage); //< Checks number of items
    ASSERT_EQ(0, visitor.mNumSparty);
    ASSERT_EQ(1, visitor.mNumXRay);

    //Test level 2 counts
    Level levelTwo(IDM_LEVEL_LEVEL2);

    TestDeclarationVisitor visitorTwo;

    for (auto item : *levelTwo.GetItems())
    {
        item->GetDeclaration()->Accept(&visitorTwo);
    }

    ASSERT_EQ(2, visitorTwo.mNumBackground);
    ASSERT_EQ(2, visitorTwo.mNumContainer);
    ASSERT_EQ(65, visitorTwo.mNumNumber);
    ASSERT_EQ(68, visitorTwo.mNumSingleImage);
    ASSERT_EQ(0, visitorTwo.mNumSparty);
    ASSERT_EQ(1, visitorTwo.mNumXRay);
}


