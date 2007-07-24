#include "LeftOpenGLCoordinateSystem.h"


namespace XOR {

LeftOpenGLCoordinateSystem *
    LeftOpenGLCoordinateSystem::_leftOpenGLCoordinateSystem = NULL;

/*
 * Protected constructor
 */
LeftOpenGLCoordinateSystem::LeftOpenGLCoordinateSystem()
{
	_rotations[0] = Rotate::CreateRotate(90.0,0,1,0, Rotate::ORIGIN);
	_rotations[1] = Rotate::CreateRotate(0,0,0,0, Rotate::ORIGIN);
	_rotations[2] = Rotate::CreateRotate(0,0,0,0, Rotate::ORIGIN);
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

