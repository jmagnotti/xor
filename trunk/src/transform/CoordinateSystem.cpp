#include "CoordinateSystem.h"

namespace XOR {

/*
 * protected constructor
 */
CoordinateSystem::CoordinateSystem()
{
	_zInvertScale = new Scale();
}


/*
 * Apply the rotates
 */
void CoordinateSystem::push(void)
{
	_zInvertScale->push();
	_scale->push();
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
	_scale->pop();
	_zInvertScale->pop();
}


/*
 * clear
 */
void CoordinateSystem::clear()
{
    //you don't want to do this
}


/*
 * string representation of the component transforms
 */
void CoordinateSystem::print()
{
    /*
    char * buffer = new char[200];
    sprintf(buffer, "rot 0: %s, rot 1: %s, rot 2: %s, scale: %s, zinvert: %s",
            _rotations[0]->toString(), _rotations[1]->toString(),
            _rotations[2]->toString(), _scale->toString(),
            _zInvertScale->toString());

    */
    _zInvertScale->print();

    _scale->print();

    for(int i=0; i<3; i++)
        _rotations[i]->print();

}


}

