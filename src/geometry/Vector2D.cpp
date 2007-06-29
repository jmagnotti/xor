#include "Vector2D.h"


namespace XOR {

/*
 * Default Constructor
 */
Vector2D::Vector2D()
{}


/*
 * Explicit Constructor
 */
Vector2D::Vector2D(float value)
{
    for (int i=0; i<2; i++)
        _position[i] = value;
}


/*
 * Explicit Constructor
 */
Vector2D::Vector2D(float x, float y)
{
    _position[0] = x;
    _position[1] = y;
}


/*
 * Explicit Constructor
 */
Vector2D::Vector2D(float points[2])
{
    for (int i=0; i<2; i++)
        _position[i] = points[i];
}


/*
 * Increment
 */
void Vector2D::increment(Vector2D * other)
{
    for(int i=0; i<2; i++)
        _position[i] += other->_position[i];
}

/*
 * Easy subtraction
 */
Vector2D * Vector2D::operator - (Vector2D * other)
{
    return new Vector2D( _position[0] - other->getX(), 
                         _position[1] - other->getY());
}


/*
 * Easy addition
 */
Vector2D * Vector2D::operator + (Vector2D * other)
{
    return new Vector2D( _position[0] + other->getX(), 
                         _position[1] + other->getY());
}

float Vector2D::get(int dimension) 
{
	if (dimension < 2 && dimension >= 0)
		return _position[dimension];
	else
		return 0;
}

float Vector2D::getX() 
{
   	return _position[0];
}

float Vector2D::getY() 
{
   	return _position[1];
}


/*
 * return -1*position
 */
Vector2D * Vector2D::invert()
{
	return new Vector2D(- _position[0],
						- _position[1]);
}


/*
 * pos[i]+=other[i]
 */
void Vector2D::increment(float position[2])
{
	for(int i=0; i<2; i++)
		_position[i] += position[i];
}

void Vector2D::increment(float a, float b)
{
	_position[0] += a;
	_position[1] += b;
}

/*
 * sets the position of the vec
 */
void Vector2D::setPosition(float position[2])
{
	for(int i=0; i<2; i++)
		_position[i] = position[i];
}


void Vector2D::setPosition(int position, float value)
{
	if (position == 0 || position == 1)
		_position[position] = value;
}


/*
 * toArray
 */
float * Vector2D::toArray()
{
	return _position;
}


/*
 * copy the other Vector2D's position
 */
void Vector2D::clone(Vector2D * other)
{
	for(int i=0; i<2; i++)
		_position[i] = other->_position[i];
}


/*
 * returns a cloned instance
 */
Vector2D * Vector2D::clone()
{
    return new Vector2D(_position);
}


/**
 * to String()
 */
char * Vector2D::toString()
{
    char * buffer = new char[60];
	sprintf(buffer, "%f %f", getX(), getY());

    return buffer;
}

}

