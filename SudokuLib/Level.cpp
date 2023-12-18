/**
 * @file Level.cpp
 * @author hankm
 */

#include "pch.h"
#include <memory>
#include "Sparty.h"
#include "Level.h"
#include "ids.h"
#include "NumberDeclaration.h"
#include "XRayDeclaration.h"
#include "BackgroundDeclaration.h"
#include "ContainerDeclaration.h"
#include "SpartyDeclaration.h"
#include "Background.h"
#include "Xray.h"
#include "Given.h"
#include "Digit.h"
#include "Container.h"
#include "XRayRetrieveVisitor.h"

using namespace std;

/// Level zero filename.
const wstring LevelZeroFileName = L"resources/levels/level0.xml";

/// Level one filename.
const wstring LevelOneFileName = L"resources/levels/level1.xml";

/// Level two filename.
const wstring LevelTwoFileName = L"resources/levels/level2.xml";

/// Level three filename.
const wstring LevelThreeFileName = L"resources/levels/level3.xml";

/// Subtract this from the level id to get the actual level number.
const int LevelOffset = 6000;

/// The amount of time to display the message for.
const int DisplayMessageTime = 3;

/// Alert message for Sparty full Xray
const wstring FullMessage = L"I'm Full!";

/// Alert message for Sparty Regurgitating on occupied spot
const wstring TakenMessage = L"Something is already there!";

/**
 * Constructor for Level, takes the Level number then loads in the relevant data for the level.
 * @param level
 */
Level::Level(int level)
{
    mLevelNumber = level;
    mScoreboard = make_shared<Scoreboard>();
    mSudokuBoard = make_shared<SudokuBoard>(this);
    mLevelBeginMessage = make_shared<LevelBeginMessage>(to_wstring(level - LevelOffset));
    mLevelEndMessage = make_shared<LevelEndMessage>();
    mSolved = false;
    Load();
}

/**
 * Returns the relevant level file based on the current level attribute.
 * @return Level filename.
 */
wxString Level::GetLevelFile()
{
    switch (mLevelNumber)
    {
        case IDM_LEVEL_LEVEL0:
            return LevelZeroFileName;

        case IDM_LEVEL_LEVEL1:
            return LevelOneFileName;

        case IDM_LEVEL_LEVEL2:
            return LevelTwoFileName;

        case IDM_LEVEL_LEVEL3:
            return LevelThreeFileName;
    }

    return L"";
}

/**
 * Draws in all the necessary attributes for Level.
 * @param graphics The graphics context to display on.
 */
void Level::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }

    mSparty->Draw(graphics);

    for (auto alert : mAlerts)
    {
        alert->Draw(graphics, GetPixelWidth());
    }

    if ((!mDone && mElapsed >= DisplayMessageTime) || mDone)
    {
        mScoreboard->Draw(graphics);
    }

    if (!mDone && mElapsed < DisplayMessageTime)
    {
        mLevelBeginMessage->Draw(graphics, GetPixelWidth(), GetPixelHeight());
    }
    else if (mDone && mElapsed < DisplayMessageTime)
    {
        mLevelEndMessage->Draw(graphics, GetPixelWidth(), GetPixelHeight());
    }
}

/**
 * Removes alerts that have moved off the screen.
 */
void Level::RemoveOldAlerts()
{
    bool clean = false;
    while (!clean)
    {
        clean = true;
        for (auto it = mAlerts.begin(); it != mAlerts.end(); ++it)
        {
            if ((*it)->ReadyForDelete())
            {
                mAlerts.erase(it);
                clean = false;
                break;
            }
        }
    }
}

/**
 * Update the items in level to the new elapsed time.
 * @param elapsed The amount of elapsed time.
 */
void Level::Update(double elapsed)
{
    mElapsed += elapsed;
    if (!mDone && mElapsed >= DisplayMessageTime)
    {
        for(auto item : mItems)
        {
            item->Update(elapsed);
        }
        for (auto alert : mAlerts)
        {
            alert->Update(elapsed);
        }
        RemoveOldAlerts();
        mScoreboard->Update(elapsed);
        mSparty->Update(elapsed);

        //If Level 3 is the current level update toxicity of Xray for team feature
        if (mLevelNumber == IDM_LEVEL_LEVEL3)
        {
            //Get pointer to the Xray
            XRayRetrieveVisitor xRayVisitor;
            Accept(&xRayVisitor);
            //Update toxicity level for the Xray
            xRayVisitor.ReturnXRay()->UpdateToxicity(elapsed);
        }
    }
    else
    {
        if (mElapsed > DisplayMessageTime)
        {
            if (mSolved)
            {
                NextLevel();
            }
            else
            {
                Load();
            }
        }
    }
}

/**
 * Add an item to the Level
 * @param item New item to add
 */
void Level::Add(std::shared_ptr<Item> item)
{
    item->SetLocation(0, 0);
    mItems.push_back(item);
}

/**
 * Clear the level data.
 *
 * Deletes items from level.
 */
void Level::Clear()
{
    mElapsed = 0;
    mScoreboard->Reset();
    mDone = false;
    mSolved = false;
    mLevelBeginMessage->SetLevelNum(to_wstring(mLevelNumber - LevelOffset));
    mAlerts.clear();
    mItems.clear();
}

/**
 * Opens the XML file and reads the nodes, creating items as appropriate.
 */
void Level::Load()
{
    wxString filename = GetLevelFile();

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Game file");
        return;
    }

    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    // Get height and width for game
    root->GetAttribute(L"width").ToInt(&mWidth);
    root->GetAttribute(L"height").ToInt(&mHeight);
    root->GetAttribute(L"tilewidth").ToInt(&mTileWidth);
    root->GetAttribute(L"tileheight").ToInt(&mTileHeight);

    // We need to ensure that we always get Declarations before Items so we get the pointers to
    // declarations, game, and items first then traverse them in order. We setup a temporary map
    // of ids to pointers so that we can connect items to their declarations.
    wxXmlNode* declarations;
    wxXmlNode* game;
    wxXmlNode* items;
    unordered_map<wstring, shared_ptr<Declaration>> declarationMap = {};

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"declarations")
        {
            declarations = child;
        }
        else if(name == L"game")
        {
            game = child;
        }
        else if(name == L"items")
        {
            items = child;
        }

    }

    child = declarations->GetChildren();
    for ( ; child; child=child->GetNext())
    {
        XmlDeclaration(child, declarationMap);
    }

    XmlGame(game);

    child = items->GetChildren();
    for ( ; child; child=child->GetNext())
    {
        XmlItem(child, declarationMap);
    }
}

/**
 * Loads in the declarations.
 * @param node
 * @param declarationMap
 */
void Level::XmlDeclaration(wxXmlNode* node, unordered_map<wstring, shared_ptr<Declaration>>& declarationMap)
{
    shared_ptr<Declaration> declaration;

    // We have a declaration. What type?
    auto type = node->GetName();
    if (type == L"given")
    {
        declaration = make_shared<NumberDeclaration>();
    }
    else if (type == L"digit")
    {
        declaration = make_shared<NumberDeclaration>();
    }
    else if (type == L"xray")
    {
        declaration = make_shared<XRayDeclaration>();
    }
    else if (type == L"background")
    {
        declaration = make_shared<BackgroundDeclaration>();
    }
    else if (type == L"container")
    {
        declaration = make_shared<ContainerDeclaration>();
    }
    else if (type == L"sparty")
    {
        declaration = make_shared<SpartyDeclaration>();
    }

    if (declaration != nullptr)
    {
        declarationMap[node->GetAttribute(L"id").ToStdWstring()] = declaration;
        declaration->XmlLoad(node);
    }
}

/**
 * Loads in the game.
 * @param node
 */
void Level::XmlGame(wxXmlNode* node)
{
    mSudokuBoard->XmlLoad(node);
}

/**
 * Loads the items into the level.
 * @param node
 * @param declarationMap
 */
void Level::XmlItem(wxXmlNode* node, std::unordered_map<std::wstring, std::shared_ptr<Declaration>>& declarationMap)
{
    // A pointer for the item we are loading
    shared_ptr<Item> item;

    // We have an item. What type?
    auto type = node->GetName();
    if (type == L"background")
    {
        item = make_shared<Background>(this);
    }
    else if (type == L"xray")
    {
        item = make_shared<Xray>(this);
    }
    else if (type == L"given")
    {
        item = make_shared<Given>(this);
    }
    else if (type == L"digit")
    {
        item = make_shared<Digit>(this);
    }
    else if (type == L"container")
    {
        // The container needs to load in the digits inside of it
        auto container = make_shared<Container>(this);
        container->XmlLoad(node, declarationMap);
        item = container;
    }
    else if (type == L"sparty") {
        mSparty = make_shared<Sparty>(this);
        item = mSparty;
        item->SetDeclaration(declarationMap[node->GetAttribute(L"id").ToStdWstring()]);
        item->XmlLoad(node);
        return;
    }

    if (item != nullptr)
    {
        Add(item);
        item->SetDeclaration(declarationMap[node->GetAttribute(L"id").ToStdWstring()]);
        item->XmlLoad(node);
    }
}

/**
 * Set the level to a different level.
 * @param level The level to set too.
 */
void Level::SetLevel(int level)
{
    mLevelNumber = level;
    mScoreboard->Reset();
    Load();
}

/**
 * Accept a visitor for the level
 * @param visitor The visitor for the collection
 */
void Level::Accept(ItemVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Command to move sparty.
 * @param x The new x coordinate.
 * @param y The new y coordinate.
 */
void Level::OnLeftDown(double x, double y)
{
    // mouse clicking has no effect during the message displaying time
    if (mElapsed > DisplayMessageTime)
    {
        // clicking only works if it is within the background
        if(x < GetPixelWidth() && x > 0 && y > 0 && y < GetPixelHeight())
        {
            mSparty->OnLeftDown(x, y, mTileWidth, mTileHeight);
        }
    }
}

/**
 * Command for sparty to headbutt.
 */
void Level::SpartyHeadbutt()
{
    mSparty->Headbutt();
}

/**
 * Command for sparty to regurgitate a number.
 * @param number The number to regurgitate.
 */
void Level::SpartyRegurgitate(int number)
{
    mSparty->Regurgitate(number);
}

/**
 * Command for sparty to eat.
 */
void Level::SpartyEat()
{
    mSparty->Eat();
}

/**
 * Solve the level.
 */
void Level::Solve()
{
    mSudokuBoard->Solve();
    CheckSolve();
}

/**
 * Check if the level is solved and if it is advance to the next level.
 */
void Level::CheckSolve()
{
    if (mSudokuBoard->IsFull())
    {
        mElapsed = 0;
        mDone = true;
        if (mSudokuBoard->IsSolved())
        {
            mSolved = true;
            mLevelEndMessage->SetSuccessStatus();
        }
        else
        {
            mSolved = false;
            mLevelEndMessage->SetFailureStatus();
        }
    }
}

/**
 * Advance to next appropriate level.
 */
void Level::NextLevel()
{
    if (mLevelNumber != IDM_LEVEL_LEVEL3)
    {
        ++mLevelNumber;
    }
    Load();
}

/**
 * Adds an alerts that sparty is full.
 */
void Level::AlertFull()
{
    auto alert = make_shared<Alert>(FullMessage, GetPixelHeight());
    mAlerts.push_back(alert);
}

/**
 * Adds an alert that a space already has a number in it.
 */
void Level::AlertSpaceTaken()
{
    auto alert = make_shared<Alert>(TakenMessage, GetPixelHeight());
    mAlerts.push_back(alert);
}
