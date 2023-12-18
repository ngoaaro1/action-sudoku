/**
 * @file XRayRetrieveVisitor.h
 * @author Devon FoxElster
 *
 * Contains class that defines a visitor class for retrieving digits inside of Xray
 */

#ifndef PROJECT1_SUDOKULIB_XRAYRETRIEVEVISITOR_H
#define PROJECT1_SUDOKULIB_XRAYRETRIEVEVISITOR_H

#include "ItemVisitor.h"
#include "Container.h"

/**
 * Visitor class to retrieve the digits inside of the Xray
 */
class XRayRetrieveVisitor : public ItemVisitor
{
private:
    Xray *mXRay; ///< Xray item to hold the found Xray

public:
    /**
     * XRay Visitor Constructor
     */
    XRayRetrieveVisitor() : ItemVisitor() {}
    /**
     * Visitor Function for XRay
     * @param xray XRay object we are visiting
     */
    void VisitXray(Xray* xray) override { mXRay = xray; }

    /**
     * Getter function for the found Xray item
     * @return Xray object associated with the level
     */
    Xray* ReturnXRay() { return mXRay; }
};

#endif //PROJECT1_SUDOKULIB_XRAYRETRIEVEVISITOR_H
