#ifndef RECTANGLE2D_H
#define RECTANGLE2D_H


#include "Object2D.h"
#include "../geometry/Vector2D.h"
#include "../geometry/Vector3D.h"
#include "../geometry/Dimension2D.h"
#include "../paint/Paint.h"


namespace XOR {

/**
 * 
 */
class Rectangle2D : public Object2D
{

public:

    /*
	 * Default Constructor.
	 */
    Rectangle2D();


    /*
	 * Explicit Constructor.
	 * Four corners and a default white paint.
	 */
    Rectangle2D(Vector2D * p0, Vector2D * p1);


    /**
	 * Explicit Constructor.
	 * Four corners and a paint.  
	 */
    Rectangle2D(Vector2D * p0, Vector2D * p1, Paint * paint);


    /**
	 * return a clone of the base point
	 */
    Vector2D* getBaseVector();


    /**
	 * return a clone of the size
	 */
    Dimension2D * getDimension();


    /**
	 * status print out
	 */
    void print();


    /**
	 * Draws the rectangle.
	 * Is doing texture stuff right now, which I may be mixing burdens.
	 */
    void renderObject();


    /**
	 * set the paint for the object
	 */
    void setPaint(Paint * paint);


private:

	Vector2D * _start, * _finish;
	Paint * _paint;

};

}

#endif			// RECTANGLE2D_H

