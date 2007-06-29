#include "Rotate.h"


namespace XOR {

const Vector3D * Rotate::PITCH  = new Vector3D(1,0,0);
const Vector3D * Rotate::YAW    = new Vector3D(0,1,0);
const Vector3D * Rotate::ROLL   = new Vector3D(0,0,1);

/*
 * Destructor
 */
Rotate::~Rotate()
{}


/*
 * Default Constructor
 */
Rotate::Rotate()
{
    _angle = 0.0f;

    //_values.push_back(&_angle);

    _xCoord = _yCoord = _zCoord = 0;
}


/*
 * Explicit constructor
 */
Rotate::Rotate(float angle, float x, float y, float z)
{
	_angle = angle;
	//_angle = GraphicsConversionUtility::GetInstance()->floatModulus(angle + 360.0f, 360);
	//cout << _angle << endl;

	_xCoord	= x;
	_yCoord	= y;
	_zCoord	= z;

    //_values.push_back(&_angle);
}

Rotate::Rotate(float angle, const Vector3D * axis)
{
	_angle = angle;
	_xCoord = axis->getX();
	_yCoord = axis->getY();
	_zCoord = axis->getZ();
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

void Rotate::print()
{
    cout << "ang: " << _angle << ", x: " << _xCoord << ", y: " << _yCoord 
         << ", z: " << _zCoord << endl;
}

void Rotate::toIdentity()
{
    _angle = 0.0f;
}

Rotate * Rotate::CreateRotate(float angle, const Vector3D * axis)
{
	return new ImmediateRotate(angle, axis);
}

Rotate * Rotate::CreateRotate(float angle, float x, float y, float z)
{
	return new ImmediateRotate(angle, x, y, z);
}

Rotate * Rotate::CreateRotate(float angle, const Vector3D * axis, int milliseconds)
{
	return new InterpolatedRotate(angle, axis, milliseconds);
}


Rotate * Rotate::CreateRotate(float angle, float x, float y, float z, int milliseconds)
{
	return new InterpolatedRotate(angle, x, y, z, milliseconds);
}

//TODO Fill these in
void Rotate::transform(Vector3D * position){}
void Rotate::transform(Dimension3D * size){}
void Rotate::transform(Vector2D * position){}
void Rotate::transform(Dimension2D * size){}
//Rotate * Rotate::createTransformedInstance(Vector3D * point){}
//Rotate * Rotate::createTransformedInstance(Vector3D * point, int milliseconds){}
//END TODO

float Rotate::getAngle()
{
	return _angle;
}

void InterpolatedRotate::push()
{
	if (_remaining > 0) {
		_angle += _step;
        
        _remaining--;
    }

    Rotate::push();
}

void InterpolatedRotate::pushInverse()
{
	if (_remaining > 0) {
		_angle += _step;
        
        _remaining--;
    }

    Rotate::pushInverse();
}

/**
 * CTOR for InterpolatedRotate
 */
InterpolatedRotate::InterpolatedRotate(float angle, const Vector3D * axis, int milliseconds) :
    Rotate(angle, axis) {
       //do something with the time 
}

InterpolatedRotate::InterpolatedRotate(float angle, float x, float y, float z, int milliseconds) :
    Rotate(angle, x, y, z) {}

ImmediateRotate::ImmediateRotate(float angle, const Vector3D * axis) 
    : Rotate(angle, axis) {}

ImmediateRotate::ImmediateRotate(float angle, float x, float y, float z) 
    : Rotate(angle, x, y, z) {}

}

