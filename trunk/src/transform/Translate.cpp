#include "Translate.h"


namespace XOR {


/*
 * Def. Constructor
 */
Translate::Translate()
{
	_xShift = _yShift = _zShift = 0;

    _values.push_back(& _xShift);
    _values.push_back(& _yShift);
    _values.push_back(& _zShift);
}


/* 
 * explicit constructor
 */
Translate::Translate(float x, float y, float z)
{
	_xShift = x;
	_yShift = y;
	_zShift = z;

    _values.push_back(& _xShift);
    _values.push_back(& _yShift);
    _values.push_back(& _zShift);
}


/*
 * Explicit Constructor
 */
Translate::Translate(Vector3D * p)
{
	_xShift = p->getX();
	_yShift = p->getY();
	_zShift = p->getZ();

    _values.push_back(& _xShift);
    _values.push_back(& _yShift);
    _values.push_back(& _zShift);
}


/*
 * Clone copier
 */
void Translate::clone(Translate * other)
{
    _xShift = other->_xShift;
    _yShift = other->_yShift;
    _zShift = other->_zShift; 
}


/* 
 * Add the point to the current translate
 */
void Translate::increment(Vector3D * point, InterpolationEngine * interpolation)
{
    if (interpolation != NULL) {
        _out.clear();
        _out.push_back(_xShift + point->getX());
        _out.push_back(_yShift + point->getY());
        _out.push_back(_zShift + point->getZ());

        interpolation->setup(_values, _out);
        interpolation->start();
    }
    else {
        _xShift += point->getX();
        _yShift += point->getY();
        _zShift += point->getZ();
    }
}


/*
 * Set the translation coordinates
 */
void Translate::set(Vector3D * point, InterpolationEngine * interpolation)
{
    if (interpolation != NULL) {
        _out.clear();
        _out.push_back(point->getX());
        _out.push_back(point->getY());
        _out.push_back(point->getZ());

        interpolation->setup(_values, _out);
        interpolation->start();
    }
    else {
        _xShift = point->getX();
        _yShift = point->getY();
        _zShift = point->getZ();
    }
}


/* 
 * apply the translate
 */
void Translate::push()
{
	glPushMatrix();
	glTranslatef(_xShift, _yShift, _zShift);
}


/* 
 * apply the translate in reverse
 */
void Translate::pushInverse()
{
	glPushMatrix();
	glTranslatef(-(_xShift), -(_yShift), -(_zShift));
}

/*
 * set trans to 0
 */
void Translate::clear()
{
    _xShift = _yShift = _zShift = 0.0f;
}

Vector3D * Translate::toVector()
{
	return new Vector3D(_xShift, _yShift, _zShift);
}


}

