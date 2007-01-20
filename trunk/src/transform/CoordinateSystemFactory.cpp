#include "CoordinateSystemFactory.h"


namespace XOR {

/*
 * defined in CoordinateSystemFactory.h
    const int CoordinateSystemFactory::OPENGL_COORDINATE_SYSTEM  = 0;
    const int CoordinateSystemFactory::MATH_COORDINATE_SYSTEM    = 1;
*/

CoordinateSystem * CoordinateSystemFactory::_defaultCoordinateSystem = NULL;

void CoordinateSystemFactory::SetDefaultCoordinateSystem(const int coordinateSystem)
{
    CoordinateSystemFactory::_defaultCoordinateSystem =
        CoordinateSystemFactory::GetCoordinateSystem(coordinateSystem);
}


/*
 *
 */
CoordinateSystem * CoordinateSystemFactory::GetDefaultCoordinateSystem()
{
    if (_defaultCoordinateSystem == NULL)
        _defaultCoordinateSystem = OpenGLCoordinateSystem::GetInstance();

    return _defaultCoordinateSystem;
}


/*
 *
 */
CoordinateSystem * CoordinateSystemFactory::GetCoordinateSystem(const int coordinateSystem)
{
    switch (coordinateSystem) {

        case MATH_COORDINATE_SYSTEM :
            return MathCoordinateSystem::GetInstance();
            break;
		
		case LEFT_OPENGL_COORDINATE_SYSTEM :
			return LeftOpenGLCoordinateSystem::GetInstance();
			break;

		case ENGINEER_COORDINATE_SYSTEM :
			return EngineerCoordinateSystem::GetInstance();
			break;

        default:
            return OpenGLCoordinateSystem::GetInstance();
            break;
    }
}

}

