#include "Rotate.h"


namespace XOR {

/*
 * Destructor
Rotate::~Rotate()
{
    _values.clear();
    _out.clear();
}
 */


/*
 * Default Constructor
 */
Rotate::Rotate()
{
    _angle = 0.0f;

    _values.push_back(&_angle);

    _xCoord = _yCoord = _zCoord = 0;
}


/*
 * Explicit constructor
 */
Rotate::Rotate(float angle, int x, int y, int z)
{
	_angle = angle;
	//_angle = GraphicsConversionUtility::GetInstance()->floatModulus(angle + 360.0f, 360);
	//cout << _angle << endl;

	_xCoord	= x;
	_yCoord	= y;
	_zCoord	= z;

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
        _angle = GraphicsConversionUtility::GetInstance()->floatModulus(_angle, 360);
    }
}
*/
 
/*
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
*/


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
}

//TODO Fill these in
void transform(Vector3D * position){}
void transform(Dimension3D * size){}
//END TODO

void Rotate::print()
{
    cout << "ang: " << _angle << ", x: " << _xCoord << ", y: " << _yCoord 
         << ", z: " << _zCoord << endl;
}

void Rotate::toIdentity()
{
    _angle = 0.0f;
}

void Rotate::transform(Vector3D * position){}
void Rotate::transform(Dimension3D * size){}

}

