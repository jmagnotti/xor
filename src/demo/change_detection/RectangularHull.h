#ifndef RECTANGULARHULL_H
#define RECTANGULARHULL_H


#include "../../xor.h"

using namespace XOR;

/**
 * A variable sized rectangular hull
 */
class RectangularHull
{

public:

    /**
     * Explicit Constructor. Takes the origin point of the hull and its
     * dimensionality.
     */
    RectangularHull(Vector2D * origin, Dimension2D * dimension);


    /**
     * Checks point for collision with hull. If point is not inside, the 
     * hull, the hull is adjusted to include it.
     */
    void adjustFor(Vector2D * point);


    /**
     * Returns the dimensions of the hull
     */
    Dimension2D* getDimension();
    
    /**
     * Returns the hull Dimensions
     */
    Dimension2D * getHull();

    /**
     * Returns the origin point of the hull
     */
    Vector2D* getOrigin();


    /**
     * Returns whether or not the specified x and y are in the hull
     */
    bool inHull(int xPos, int yPos);

    /**
     * Returns whether or not the vector is in the hull
     */
    bool inHull(Vector2D * point);

    Vector2D * getCentroid();


private:
	Dimension2D * _dimension;
	Vector2D * _origin;
};


#endif			// RECTANGULARHULL_H

