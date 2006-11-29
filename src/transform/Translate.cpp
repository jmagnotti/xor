#include "Translate.h"

#include <iostream>

using namespace std;


namespace XOR {

/* 
 * explicit constructor
 */
Translate::Translate(float x, float y, float z)
{
	_xShift = x;
	_yShift = y;
	_zShift = z;
}

/*
 * Explicit Constructor
 */
Translate::Translate(Point3D *p)
{
	_xShift = p->getX();
	_yShift = p->getY();
	_zShift = p->getZ();
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
void Translate::increment(Point3D * point)
{
	_xShift += point->getX();
	_yShift += point->getY();
	_zShift += point->getZ();
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
