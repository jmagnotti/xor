#include "OpenGLCoordinateSystem.h"


namespace XOR {

OpenGLCoordinateSystem * OpenGLCoordinateSystem::_openGLCoordinateSystem =
    NULL;

/*
 * Protected constructor
 */
OpenGLCoordinateSystem::OpenGLCoordinateSystem()
{
    _xRotation = new Rotate();
    _yRotation = new Rotate();
    _zRotation = new Rotate();
}


/*
 * Singleton accessor
 */
CoordinateSystem * OpenGLCoordinateSystem::GetInstance()
{
    if (_openGLCoordinateSystem == NULL)
        _openGLCoordinateSystem = new OpenGLCoordinateSystem();

    return _openGLCoordinateSystem;
}

}

