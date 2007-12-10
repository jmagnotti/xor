#ifndef HOTSPOTGRID_H
#define HOTSPOTGRID_H

#include "../../xor.h"
#include "ActionItem.h"
#include <vector>
#include "RectangularHull.h"
#include "LightweightMenu.h"

using namespace XOR;

/**
 * Hotspot grid class
 */
class HotspotGrid : public MouseListener, public Object2D//: public LightweightMenu
{
public:

    /**
     * Construct a grid with width gridSize at origin.
     */
    HotspotGrid(Vector2D * origin, Dimension2D * gridSize);


    /**
     * Adds an already constructed action item
     */
    bool addAction(ActionItem * item);


    /**
     * Builds an action item to add to the grid
     */
    bool addAction(Action * a, char * iconPath);


    /**
     * Handles the mouse click by determining which part of the grid was clicked
     * and calling performAction for the action associated with that grid location
     */
    void handleMouseEvent(MouseEvent * me);
    
    
    /**
     * Returns the origin vector of the grid
     */
    Vector2D* getBaseVector();


    /**
     * Returns the dimensions of the grid
     */
    Dimension2D* getDimension();


    /**
     * Returns the next available grid location
     */
    Vector2D* getNextLocation();


    /**
     * Draws the grid
     */
    void renderObject();


private:

    vector<ActionItem*> _actions;
	Vector2D * _origin;
    Dimension2D * _currentSize;
	Dimension2D * _maxSize;
    RectangularHull * _bounds;

};


#endif			// HOTSPOTGRID_H

