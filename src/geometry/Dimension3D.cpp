#include "Dimension3D.h"


namespace XOR {

/*
 * Default Constructor
 */
Dimension3D::Dimension3D()
{
    _dimension = new float[3];
}


/*
 * Explicit Constructor
 */
Dimension3D::Dimension3D(float rad)
{
    _dimension = new float[3];

    for (int i=0; i<3; i++)
        _dimension[i] = rad;
}


/*
 * Explicit Constructor
 */
Dimension3D::Dimension3D(float x, float y, float z)
{
    _dimension = new float[3];

    _dimension[0] = x;
    _dimension[1] = y;
    _dimension[2] = z;
}

/*
 * Explicit Constructor
 */
Dimension3D::Dimension3D(float points[3])
{
    _dimension = new float[3];

    for (int i=0; i<3; i++)
        _dimension[i] = points[i];
}




/*
 * Increment
 */
void Dimension3D::increment(Dimension3D * other)
{
    
    for(int i=0; i<3; i++)
        _dimension[i] += other->_dimension[i];
}

/*
 * Easy subtraction
 */
Dimension3D * Dimension3D::operator - (Dimension3D * dim)
{
    return new Dimension3D( _dimension[0] - dim->getWidth(), 
                            _dimension[1] - dim->getHeight(),
                            _dimension[2] - dim->getDepth() );
}


/*
 * Easy addition
 */
Dimension3D * Dimension3D::operator + (Dimension3D * dim)
{
    return new Dimension3D( _dimension[0] + dim->getWidth(), 
                            _dimension[1] + dim->getHeight(),
                            _dimension[2] + dim->getDepth() );
}

// Getters //
int     Dimension3D::getDimensionality() 			{ return 3;             }

float   Dimension3D::getWidth()     { return _dimension[0];	}
float   Dimension3D::getHeight()    { return _dimension[1]; }
float   Dimension3D::getDepth()     { return _dimension[2]; }

float   Dimension3D::getX()     { return _dimension[0];	}
float   Dimension3D::getY()     { return _dimension[1]; }
float   Dimension3D::getZ()     { return _dimension[2]; }

}
