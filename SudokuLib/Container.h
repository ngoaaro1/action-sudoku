/**
 * @file Container.h
 * @author Devon FoxElster
 *
 * File containing the Container parent class
 */

#ifndef PROJECT1_SUDOKULIB_CONTAINER_H
#define PROJECT1_SUDOKULIB_CONTAINER_H

#include "Item.h"
#include "ItemVisitor.h"
#include <random>

/**
 * Forward Reference to the Digits class in Digit.cpp / Digit.h
 */
class Digit;

/**
 * Abstract Class covering the functionality of the XRAY class and other container classes
 */
class Container : public Item
{
private:
    std::vector<std::shared_ptr<Item>> mStoredDigits;  ///< Vector containing all stored digits

    /// Random number Generator for Digit displaying
    std::mt19937 mRandomGenerator;

public:
    Container(Level* level);

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    virtual void XmlLoad(wxXmlNode* node, std::unordered_map<std::wstring, std::shared_ptr<Declaration>>& declarationMap);

    /**
     * Add an item to the container's contents
     * @param item Item to be added to contents
     */
    virtual void AddItem(std::shared_ptr<Item> item) { mStoredDigits.push_back(item); }

    /**
     * Clear contents of a container
     */
    virtual void Clear() { mStoredDigits.clear(); }

    virtual void DeleteItem(std::shared_ptr<Item> item);

    std::shared_ptr<Item> SearchContents(int val);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    virtual void Accept(ItemVisitor* visitor) override { visitor->VisitContainer(this); }

    std::vector<double> GenerateCoordinate(double minX, double maxY,
                                           double height, double width);

    void DrawDigits(std::shared_ptr<wxGraphicsContext> graphics);

    int CheckSize();

    void DisperseContents(bool resize);
};

#endif //PROJECT1_SUDOKULIB_CONTAINER_H
