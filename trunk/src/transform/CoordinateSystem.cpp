#include "CoordinateSystem.h"

namespace XOR {

/*
 * protected constructor
 */
CoordinateSystem::CoordinateSystem()
{}


/*
 * Apply the rotates
 */
void CoordinateSystem::push(void)
{
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
}


/*
 * clear
 */
void CoordinateSystem::clear()
{
    //you don't want to do this
}

}

