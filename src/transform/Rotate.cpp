#include "Rotate.h"


namespace XOR {


/*
 * Default Constructor
 */
Rotate::Rotate()
{
    _angle = 0.0f;

    //_out     = new vector<float>();
    //_values  = new vector<float*>();

    _values.push_back(&_angle);

    _xCoord = _yCoord = _zCoord = 0;
}


/*
 * Explicit constructor
 */
Rotate::Rotate(float angle, int x, int y, int z)
{
	_angle = angle;

	_xCoord	= x;
	_yCoord	= y;
	_zCoord	= z;

    //_out    = new vector<float>();
    //_values = new vector<float*>();

    _values.push_back(&_angle);
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
    if (interpolation != NULL) {
        _out.clear();
        _out.push_back(_angle + angle);

        interpolation->setup(_values, _out);
        interpolation->start();
    }
    else {
        _angle += angle;
        _angle = GraphicsConversionUtility::GetInstance()->floatModulus(_angle,
                360);
    }
}
 
void Rotate::set(float angle, InterpolationEngine * interpolation)
{
    if (interpolation != NULL) {
        _out.clear();
        _out.push_back(angle);

        interpolation->setup(_values, _out);
        interpolation->start();
    }
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

