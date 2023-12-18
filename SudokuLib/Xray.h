/**
 * @file Xray.h
 * @author Devon FoxElster
 *
 * File containing the Xray class
 */

#ifndef PROJECT1_SUDOKULIB_XRAY_H
#define PROJECT1_SUDOKULIB_XRAY_H

#include "Container.h"
#include "SudokuGame.h"

/**
 * Class handling the stomach functionality of the Sparty object
 */
class Xray : public Container
{
private:
    ///Tracks the toxicity buildup of numbers in stomach (time numbers are in Xray)
    double mToxicity = 0;

    bool CheckOccupied(); ///< Checks if at least one item is in the Xray
public:
    /**
 * Constructor for the Xray item.
 * @param level The level the xray belongs to.
 */
    Xray(Level* level) : Container(level) {}

    void Accept(ItemVisitor* visitor) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Adds item to xray
     * @param item to add to xray
     */
    void AddItem(std::shared_ptr<Item> item) override;

    bool CheckFull();

    void UpdateToxicity(double elapsed);

};

#endif //PROJECT1_SUDOKULIB_XRAY_H
