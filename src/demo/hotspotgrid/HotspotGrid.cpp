#include "HotspotGrid.h"


/**
 * Construct a grid with width gridSize at origin.
 */
HotspotGrid::HotspotGrid(Vector2D * origin, Dimension2D * gridSize)
{  
    _size = gridSize;
    _origin = origin;
    _nextAvailableSpot = origin;
    _bounds = new RectangularHull(origin, gridSize);
}


/**
 * Draws the grid
 */
void HotspotGrid::renderObject()
{
    // all actions on the grid are 2D, and we don't want to push & pop for each
    // object, therefore we are calling renderObject.
    for(int i=0; i<_actions.size(); i++)
        _actions[i]->renderObject();
}

/**
 * Handles the mouse click by determining which part of the grid was clicked
 * and calling performAction for the action associated with that grid location
 */
void HotspotGrid::handleMouseEvent(MouseEvent * me)
{
    Vector2D * tmp;
    tmp = new Vector2D(me->getXPosition(), me->getYPosition()); 

   if (_bounds->inHull(tmp)) 
   {
        for(int i = 0; i < _actions.size(); i++)
        _actions[i]->handleMouseEvent(me);
   }
}

/**
 * Returns the origin vector of the grid
 */
Vector2D * HotspotGrid::getBaseVector()
{
    return _origin->clone();
}

/**
 * Returns the dimensions of the grid
 */
Dimension2D * HotspotGrid::getDimension()
{
    return _size->clone();
}

/**
 * Returns the next available grid location
 */
Vector2D * HotspotGrid::getNextLocation()
{
    return _nextAvailableSpot->clone();
}

/**
 * Adds an already constructed action item
 */
bool HotspotGrid::addAction(ActionItem * item)
{
    //if next available spot isn't off the grid
    if(_nextAvailableSpot->getX() < (_origin->getX() + _size->getWidth())) {
        //add action item to vector
        _actions.push_back(item);       
 
        //update next available spot
        _nextAvailableSpot->setPosition(0, item->getIconHull()->getWidth());
        _nextAvailableSpot->setPosition(1, item->getIconHull()->getHeight());
        return true;
    }

    return false;
}

/**
 * Builds an action item to add to the grid
 */
bool HotspotGrid::addAction(Action * a, Dimension2D * iconSize, char * iconPath)
{
    return addAction(new ActionItem(new Icon2D(_nextAvailableSpot, iconSize, 
                                               iconPath), a));
}




