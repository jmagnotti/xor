#include "HotspotGrid.h"
#include <iostream>

using namespace std;

/**
 * Construct a grid with width gridSize at origin.
 */
HotspotGrid::HotspotGrid(Vector2D * origin, Dimension2D * gridSize)
{  
    _currentSize = new Dimension2D(0,gridSize->getHeight());
    _maxSize = gridSize;
    _origin = origin;
    _bounds = new RectangularHull(origin, _currentSize);
	//setVisible(false);
}


/**
 * Draws the grid
 */
void HotspotGrid::renderObject()
{
    // all actions on the grid are 2D, and we don't want to push & pop for each
    // object, therefore we are calling renderObject.
    for(int i=0; i< _actions.size(); i++)
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

   if (_bounds->inHull(tmp)) {
        cout << " ME in HSG, sending to _actions" << endl;
        for(int i = 0; i < _actions.size(); i++)
        _actions[i]->handleMouseEvent(me);
   }

    delete tmp;
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
    return _maxSize->clone();
}

/**
 * Returns the next available grid location
 */
Vector2D * HotspotGrid::getNextLocation()
{
    return new Vector2D(_origin->getX() + _currentSize->getWidth(), _origin->getY());
}

/**
 * Adds an already constructed action item
 */
bool HotspotGrid::addAction(ActionItem * item)
{
    //if next available spot isn't off the grid
    if(_currentSize->getWidth() < _maxSize->getWidth()) 
    {
        //add action item to vector
        _actions.push_back(item);
        //update the currentsize
        _currentSize->setWidth(_currentSize->getWidth() + item->getIconHull()->getWidth());

       _bounds->adjustFor(new Vector2D(_origin->getX() + _currentSize->getWidth(),
                                        _origin->getY() + _currentSize->getHeight()));
       return true;
    }

    return false;
}

/**
 * Builds an action item to add to the grid
 */
bool HotspotGrid::addAction(Action * a, char * iconPath)
{
    return addAction(new ActionItem(new Icon2D(getNextLocation(), new Dimension2D(_maxSize->getHeight(),_maxSize->getHeight()), iconPath), a));
}

