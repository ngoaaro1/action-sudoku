/**
 * @file ItemTest.cpp
 * @author hankm
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <Item.h>
#include <Level.h>
#include <ids.h>

using namespace std;



/**
 * Mock class to test abstract item.
 */
class ItemMock : public Item
{
public:
    ItemMock(Level* level) : Item(level) {}
    void Accept(ItemVisitor* visitor) override {};
};

/**
 * Item test fixture to test correct attributes are loaded.
 */
class ItemTest : public ::testing::Test
{
protected:

    /**
     * Allocate a node with item attributes.
     * @return Node with item attributes.
     */
    wxXmlNode* MakeTestNode()
    {
        auto node = new wxXmlNode();

        node->SetName(L"item");
        node->AddAttribute(L"id", L"i300");
        node->AddAttribute(L"row", L"5.5");
        node->AddAttribute(L"col", L"6.6");

        return node;
    }

    /**
     * Test an items XML load capabilities.
     * @param item The item to test.
     */
    void TestItem(ItemMock* item)
    {
        wxXmlNode* node = MakeTestNode();

        item->XmlLoad(node);

        ASSERT_EQ(L"i300", item->GetId());
        ASSERT_EQ(5.5, item->GetRow());
        ASSERT_EQ(6.6, item->GetCol());

        delete node;
    }
};

TEST_F(ItemTest, Construct)
{
    Level level(IDM_LEVEL_LEVEL1);
    ItemMock item(&level);
}

TEST_F(ItemTest, Load)
{
    Level level(IDM_LEVEL_LEVEL1);
    ItemMock item(&level);

    TestItem(&item);
}