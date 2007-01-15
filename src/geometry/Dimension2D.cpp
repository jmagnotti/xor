#include "Dimension2D.h"


namespace XOR {

/*
 * Default Constructor
 */
Dimension2D::Dimension2D()
{
    _dimension = new float[2];
}


/*
 * Explicit Constructor
 */
Dimension2D::Dimension2D(float width, float height)
{
    _dimension = new float[2];
    _dimension[0] = width;
    _dimension[1] = height;
}


// Getters //
int Dimension2D::getDimensionality() { return 2;             }

float Dimension2D::getWidth()	    { return _dimension[0];	}
float Dimension2D::getHeight()	    { return _dimension[1];	}

float Dimension2D::getX()	    { return _dimension[0];	}
float Dimension2D::getY()	    { return _dimension[1];	}

// Setters //
void Dimension2D::setHeight(float height) {	_dimension[1] = height; }
void Dimension2D::setWidth(float width)   { _dimension[0] = width;   }

}

