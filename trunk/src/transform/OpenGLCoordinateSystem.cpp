#include "OpenGLCoordinateSystem.h"


namespace XOR {

OpenGLCoordinateSystem * OpenGLCoordinateSystem::_openGLCoordinateSystem =
    NULL;

/*
 * Protected constructor
 */
OpenGLCoordinateSystem::OpenGLCoordinateSystem()
{
    // doesn't use the rotations
	_rotations[0] = new Rotate();
	_rotations[1] = new Rotate();
	_rotations[2] = new Rotate();
	_scale = new Scale();
}


/*
 * Singleton accessor
 */
OpenGLCoordinateSystem * OpenGLCoordinateSystem::GetInstance()
{
    if (_openGLCoordinateSystem == NULL)
        _openGLCoordinateSystem = new OpenGLCoordinateSystem();

    return _openGLCoordinateSystem;
}

void OpenGLCoordinateSystem::push()
{
    // nothing
}


void OpenGLCoordinateSystem::pop()
{
    // nothing
}

}

