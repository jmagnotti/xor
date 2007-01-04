#include "Translate.h"


namespace XOR {

/* 
 * explicit constructor
 */
Translate::Translate(float x, float y, float z)
{
	_xShift = x;
	_yShift = y;
	_zShift = z;

    //_values = new vector<float*>(); 
    //_out    = new vector<float*>(); 

    _values.push_back(& _xShift);
    _values.push_back(& _yShift);
    _values.push_back(& _zShift);
}


/*
 * Explicit Constructor
 */
Translate::Translate(Dimension3D *p)
{
	_xShift = p->getX();
	_yShift = p->getY();
	_zShift = p->getZ();

    //_values = new vector<float*>(); 
    //_out    = new vector<float*>(); 

    _values.push_back(& _xShift);
    _values.push_back(& _yShift);
    _values.push_back(& _zShift);
}


/*
 * Static constructor
 */
Translate * Translate::CreateTranslation(float x, float y, float z)
{
	return new Translate(x,y,z);
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
void Translate::increment(Dimension3D * point, InterpolationEngine * interpolation)
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
void Translate::set(Dimension3D * point, InterpolationEngine * interpolation)
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

}

