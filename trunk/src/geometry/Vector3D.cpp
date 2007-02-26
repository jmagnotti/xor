#include "Vector3D.h"


namespace XOR {

/*
 * Default Constructor
 */
Vector3D::Vector3D()
{}


/*
 * Explicit Constructor
 */
Vector3D::Vector3D(float value)
{
    for (int i=0; i<3; i++)
        _position[i] = value;
}


/*
 * Explicit Constructor
 */
Vector3D::Vector3D(float x, float y, float z)
{
    _position[0] = x;
    _position[1] = y;
    _position[2] = z;
}


/*
 * Explicit Constructor
 */
Vector3D::Vector3D(float points[3])
{
    for (int i=0; i<3; i++)
        _position[i] = points[i];
}


/*
 * Increment
 */
void Vector3D::increment(Vector3D * other)
{
    for(int i=0; i<3; i++)
        _position[i] += other->_position[i];
}

/*
 * Easy subtraction
 */
Vector3D * Vector3D::operator - (Vector3D * other)
{
    return new Vector3D( _position[0] - other->getX(), 
                         _position[1] - other->getY(),
                         _position[2] - other->getZ() );
}


/*
 * Easy addition
 */
Vector3D * Vector3D::operator + (Vector3D * other)
{
    return new Vector3D( _position[0] + other->getX(), 
                         _position[1] + other->getY(),
                         _position[2] + other->getZ() );
}

float Vector3D::get(int dimension) const
{
	if (dimension < 3 && dimension >= 0)
		return _position[dimension];
	else
		return 0;
}

float Vector3D::getX() const
{
   	return _position[0];
}

float Vector3D::getY() const
{
   	return _position[1];
}


float Vector3D::getZ() const
{
   	return _position[2];
}


/*
 * return -1*position
 */
Vector3D * Vector3D::invert()
{
	return new Vector3D(- _position[0],
						- _position[1],
						- _position[2]);
}


/*
 * pos[i]+=other[i]
 */
void Vector3D::increment(float position[3])
{
	for(int i=0; i<3; i++)
		_position[i] += position[i];
}


/*
 * sets the position of the vec
 */
void Vector3D::setPosition(float position[3])
{
	for(int i=0; i<3; i++)
		_position[i] = position[i];
}


/*
 * toArray
 */
float * Vector3D::toArray()
{
	return _position;
}


/*
 * copy the other Vector3D's position
 */
void Vector3D::clone(Vector3D * other)
{
	for(int i=0; i<3; i++)
		_position[i] = other->_position[i];
}


char * Vector3D::toString()
{
    char * buffer = new char[60];
	sprintf(buffer, "%f %f %f", getX(), getY(), getZ());

    return buffer;
}


}

