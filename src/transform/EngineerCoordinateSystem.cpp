#include "EngineerCoordinateSystem.h"


namespace XOR {

EngineerCoordinateSystem * EngineerCoordinateSystem::_engineerCoordinateSystem =
    NULL;

/*
 * Protected constructor
 */
EngineerCoordinateSystem::EngineerCoordinateSystem()
{
	_rotations[0] = Rotate::CreateRotate( 90.0,0,1,0, Rotate::ORIGIN);
	_rotations[1] = Rotate::CreateRotate(-90.0,1,0,0, Rotate::ORIGIN);
	_rotations[2] = Rotate::CreateRotate(-90.0,0,0,1, Rotate::ORIGIN);
	_scale = new Scale(1,1,-1);
}


/*
 * Singleton accessor
 */
EngineerCoordinateSystem * EngineerCoordinateSystem::GetInstance()
{
    if (_engineerCoordinateSystem == NULL)
        _engineerCoordinateSystem = new EngineerCoordinateSystem();

    return _engineerCoordinateSystem;
}

}

