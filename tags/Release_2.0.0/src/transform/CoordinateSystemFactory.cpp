#include "CoordinateSystemFactory.h"


namespace XOR {

CoordinateSystem * CoordinateSystemFactory::_defaultCoordinateSystem = NULL;

/*
 * set the defualt CS
 */
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
    cout << "CSF Called with: " << coordinateSystem << endl;
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

        case MAC_COORDINATE_SYSTEM : 
            return MacCoordinateSystem::GetInstance();
            break;

        default:
            return OpenGLCoordinateSystem::GetInstance();
            break;
    }
}

}

