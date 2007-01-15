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

void OpenGLCoordinateSystem::push()
{
    // nothing
}


void OpenGLCoordinateSystem::pop()
{
    // nothing
}

}

