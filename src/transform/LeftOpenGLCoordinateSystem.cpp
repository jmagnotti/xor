#include "LeftOpenGLCoordinateSystem.h"


namespace XOR {

LeftOpenGLCoordinateSystem *
    LeftOpenGLCoordinateSystem::_leftOpenGLCoordinateSystem = NULL;

/*
 * Protected constructor
 */
LeftOpenGLCoordinateSystem::LeftOpenGLCoordinateSystem()
{
    // doesn't use the rotations
	_rotations[0] = new Rotate(90.0,0,1,0);
	_rotations[1] = new Rotate();
	_rotations[2] = new Rotate();
	_scale = new Scale(1,1,-1);
}


/*
 * Singleton accessor
 */
LeftOpenGLCoordinateSystem * LeftOpenGLCoordinateSystem::GetInstance()
{
    if (_leftOpenGLCoordinateSystem == NULL)
        _leftOpenGLCoordinateSystem = new LeftOpenGLCoordinateSystem();

    return _leftOpenGLCoordinateSystem;
}

}

