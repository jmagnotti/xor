#include "CDGrid.h"
#include <iostream>

using namespace std;
using namespace XOR;


CDGrid::CDGrid()
{
    _origin = new Vector2D(20,20);
    _size = new Dimension2D(0,20);
    _bounds = new RectangularHull(_origin, _size);
}

void CDGrid::renderObject()
{
    if (_visible)
	for(int i=0; i<_actions.size(); i++)
	    _actions[i]->renderObject();
}

void CDGrid::handleMouseEvent(MouseEvent * me)
{
    Vector2D * tmp;
    tmp = new Vector2D(me->getXPosition(), me->getYPosition()); 

   //if (_bounds->inHull(tmp)) {
        for(int i = 0; i < _actions.size(); i++)
	    _actions[i]->handleMouseEvent(me);
   //}

    delete tmp;
}

/**
 * Returns the origin vector of the grid
 */
Vector2D * CDGrid::getBaseVector()
{
    return _origin->clone();
}

/**
 * Returns the dimensions of the grid
 */
Dimension2D * CDGrid::getDimension()
{
    return NULL;
}

/**
 * Adds an already constructed action item
 */
void CDGrid::addAction(ActionItem * item)
{
    _actions.push_back(item);
}

void CDGrid::setVisible(bool vis) {
    _visible = vis;	
}

bool CDGrid::isVisible() {
    return _visible;
}
