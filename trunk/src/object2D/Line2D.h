#ifndef LINE2D_H
#define LINE2D_H


#include "Object2D.h"
#include "../geometry/Vector2D.h"
#include "../geometry/Vector3D.h"
#include "../paint/Paint.h"


namespace XOR {

/**
 * 
 */
class Line2D : public Object2D
{

public:

    /*
	 * Default Constructor.
	 */
    Line2D();
    ~Line2D();


    /*
	 * Explicit Constructor.
	 * Two corners and a default white paint.
	 */
    Line2D(Vector2D * p0, Vector2D * p1);


    /**
	 * Explicit Constructor.
	 * Two corners and a paint.  
	 */
    Line2D(Vector2D * p0, Vector2D * p1, Paint * paint);


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
	 * Draws the line.
	 */
    void renderObject();


    /**
	 * set the paint for the object
	 */
    void setPaint(Paint * paint);


    /**
     * Returns a copy of the paint object associated with the rect
     */
    Paint * getPaint();

private:

	Vector2D * _start, * _finish;
	Paint * _paint;

};

}

#endif			// LINE2D_H

