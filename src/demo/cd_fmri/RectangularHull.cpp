#include "RectangularHull.h"
#include <iostream>

using namespace std;

/**
 * Explicit Constructor. Takes the origin point of the hull and its
 * dimensionality.
 */
RectangularHull::RectangularHull(Vector2D * origin, Dimension2D * dimension)
{
    _origin = origin;
    _dimension = dimension;
}

/**
 * Gets the dimensions of the hull
 */
Dimension2D * RectangularHull::getHull()
{
    return _dimension->clone();
}

/**
 * Checks point for collision with hull. If point is not inside, the 
 * hull, the hull is adjusted to include it.
 */
void RectangularHull::adjustFor(Vector2D * point)
{
	if(point->getX() > (_origin->getX() + _dimension->getWidth()))
		_dimension->setWidth(point->getX() - _origin->getX());
	else if(point->getX() < _origin->getX())
		_origin->setPosition(0, point->getX());


	if(point->getY() > (_origin->getY() + _dimension->getHeight()))
		_dimension->setHeight(point->getY() - _origin->getY());
	else if(point->getY() < _origin->getY())
		_origin->setPosition(1, point->getY());
}

/**
 * Returns the origin point of the hull
 */
Vector2D * RectangularHull::getOrigin()
{
    return _origin->clone();
}


/**
 * Returns the dimensions of the hull
 */
Dimension2D * RectangularHull::getDimension()
{
    return _dimension->clone();
}

/**
 * Determine if the x and y are inside the hull
 */
bool RectangularHull::inHull(int xPos, int yPos)
{     

	if(xPos >= _origin->getX() && xPos <= (_origin->getX() + _dimension->getWidth())
        && yPos >= _origin->getY() && yPos <= (_origin->getY() + _dimension->getHeight()))
    {
        return true;
    }

	 return false;
}

Vector2D * RectangularHull::getCentroid()
{
       return  new Vector2D((_dimension->getWidth()  - _origin->getX() / 2.0) + _origin->getX(),
                            (_dimension->getHeight() - _origin->getY() / 2.0) + _origin->getY());
}

/*
 * Returns whether or not the vector is in the hull
 */
bool RectangularHull::inHull(Vector2D * point)
{
    return inHull(point->getX(), point->getY());
}
