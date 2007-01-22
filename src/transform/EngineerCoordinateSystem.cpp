#include "EngineerCoordinateSystem.h"


namespace XOR {

EngineerCoordinateSystem * EngineerCoordinateSystem::_engineerCoordinateSystem =
    NULL;

/*
 * Protected constructor
 */
EngineerCoordinateSystem::EngineerCoordinateSystem()
{
	_rotations[0] = new Rotate( 90.0,0,1,0);
	_rotations[1] = new Rotate(-90.0,1,0,0);
	_rotations[2] = new Rotate(-90.0,0,0,1);
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

