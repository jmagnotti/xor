#include "MacCoordinateSystem.h"


namespace XOR {

MacCoordinateSystem * MacCoordinateSystem::_macCoordinateSystem = NULL;


/**
 * singleton accessor
 */
MacCoordinateSystem * MacCoordinateSystem::GetInstance()
{
    if (_macCoordinateSystem == NULL)
        _macCoordinateSystem = new MacCoordinateSystem();

    return _macCoordinateSystem;
}


/**
 * Initialize the Y rotation to 180 degrees.
 */
MacCoordinateSystem::MacCoordinateSystem()
{
    cout << "eh, this is not going well..." << endl;
    _rotations[0] = new Rotate();
    _rotations[1] = new Rotate(); 
    _rotations[2] = new Rotate(); 

    _scale = new Scale(1,1,-1);
}


/**
 * Apply the 180 flip in the Y direction
 */
void MacCoordinateSystem::push()
{
    _rotations[0]->push();
}


/**
 * removes the transform
 */
void MacCoordinateSystem::pop()
{
    _rotations[0]->pop();
}


}

