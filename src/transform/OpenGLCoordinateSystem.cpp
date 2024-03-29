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
	//_rotations[0] = Rotate::CreateRotate(0,0,0,0);
	//_rotations[1] = Rotate::CreateRotate(0,0,0,0);
	//_rotations[2] = Rotate::CreateRotate(0,0,0,0);
	//_scale = new Scale();
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

void OpenGLCoordinateSystem::print()
{
    cout << "no coord sys transforms applied" << endl;
}


void OpenGLCoordinateSystem::pop()
{
    // nothing
}

}

