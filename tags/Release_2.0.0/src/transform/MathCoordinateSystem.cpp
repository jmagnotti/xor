#include "MathCoordinateSystem.h"


namespace XOR {

MathCoordinateSystem * MathCoordinateSystem::_mathCoordinateSystem =
    NULL;

/*
 * Protected constructor
 */
MathCoordinateSystem::MathCoordinateSystem()
{
	_rotations[0] = Rotate::CreateRotate(-90.0,1,0,0);
	_rotations[1] = Rotate::CreateRotate(-90.0,0,0,1);
	_rotations[2] = Rotate::CreateRotate(0,0,0,0, Rotate::ORIGIN);
	_scale = new Scale();
}


/*
 * Singleton accessor
 */
CoordinateSystem * MathCoordinateSystem::GetInstance()
{
    if (_mathCoordinateSystem == NULL)
        _mathCoordinateSystem = new MathCoordinateSystem();

    return _mathCoordinateSystem;
}

}

