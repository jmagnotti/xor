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
 * string cstr
 */
Dimension3D::Dimension3D(char * vals)
{
    char * result = NULL;
    char delims[] = " ";

    _dimension = new float[3];

    result = strtok(vals, delims); 
    _dimension[0] = atof(result);

    for (int i=1; i<3; i++) {
        result = strtok(NULL, delims); 
        _dimension[i] = atof(result);
    }
}


// Getters //
int     Dimension3D::getDimensionality() 			
                                    { return 3;             }

float   Dimension3D::getWidth()     { return _dimension[0];	}
float   Dimension3D::getHeight()    { return _dimension[1]; }
float   Dimension3D::getDepth()     { return _dimension[2]; }


/*
 * returns the dimension as a vector
 */
Vector3D * Dimension3D::toVector()
{
    return new Vector3D(_dimension);
}

}

