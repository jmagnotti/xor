#include "CoordinateSystem.h"

namespace XOR {

CoordinateSystem::CoordinateSystem()
{}


/*
 * Apply the rotates
 */
void CoordinateSystem::push(void)
{
    _xRotation->push();
    _yRotation->push();
    _zRotation->push();
}


/*
 * Remove the rotates 
 */
void CoordinateSystem::pop(void)
{
    _zRotation->pop();
    _yRotation->pop();
    _xRotation->pop();
}


}
