#include "CoordinateSystem.h"

namespace XOR {

/*
 * protected constructor
 */
CoordinateSystem::CoordinateSystem()
{
}

void CoordinateSystem::pushInverse(void)
{
    //you don't want to do this
}

/*
 * Apply the rotates
 */
void CoordinateSystem::push(void)
{
//	_zInvertScale->push();
	//_scale->push();
    for(int i=0; i<3; i++)
        _rotations[i]->push();
}


/*
 * Remove the rotates 
 */
void CoordinateSystem::pop(void)
{
    for (int i=2; i>=0; i--)
        _rotations[i]->pop();
	//_scale->pop();
//	_zInvertScale->pop();
}


/*
 * clear
 */
void CoordinateSystem::toIdentity()
{
    //you don't want to do this
}


/*
 * string representation of the component transforms
 */
void CoordinateSystem::print()
{
    //_scale->print();

    for(int i=0; i<3; i++)
        _rotations[i]->print();
}

void CoordinateSystem::transform(Dimension3D * size)
{
    // shouldn't be used
}

void CoordinateSystem::transform(Vector3D * position)
{
    // shouldn't be used
}

}

