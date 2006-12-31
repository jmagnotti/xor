#include "Rotate.h"


namespace XOR {


/*
 * Default Constructor
 */
Rotate::Rotate()
{
    _angle = .0f;
    _xCoord = _yCoord = _zCoord = 0;
}


/*
 * Explicit constructor
 */
Rotate::Rotate(float ang, int x, int y, int z)
{
	_angle		= ang;

	_xCoord	= x;
	_yCoord	= y;
	_zCoord	= z;
}


/**
 * Clone copier
 */
void Rotate::clone(Rotate * other)
{
    _angle = other->_angle;

    _xCoord = other->_xCoord;
    _yCoord = other->_yCoord;
    _zCoord = other->_zCoord;
}

/* 
 * increment the rotation values
 */
void Rotate::increment(float angle, InterpolationEngine * interpolation)
{
    if (interpolation != NULL)
    {}
    else
        _angle += angle;
}
 
void Rotate::set(float angle, InterpolationEngine * interpolation)
{
    if (interpolation != NULL)
    {}
    else
        _angle = angle;
}    


/*
 * pushes a matrix then applies the rotate
 */
void Rotate::push()
{
	glPushMatrix();
	glRotatef(_angle, _xCoord, _yCoord, _zCoord);
}


/*
 * pushes a matrix then applies the rotate (in reverse)
 */
void Rotate::pushInverse()
{
	glPushMatrix();
	glRotatef(-(_angle), _xCoord, _yCoord, _zCoord);

    // quaternions
}

}

