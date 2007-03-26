#ifndef COORDINATESYSTEMFACTORY_H
#define COORDINATESYSTEMFACTORY_H


#include "CoordinateSystem.h"
#include "OpenGLCoordinateSystem.h"
#include "MacCoordinateSystem.h"
#include "MathCoordinateSystem.h"
#include "LeftOpenGLCoordinateSystem.h"
#include "EngineerCoordinateSystem.h"


namespace XOR { 

/**
 *
 */
class CoordinateSystemFactory
{

public: 

    /**
     * Coordinate System Constants. Use these to select a coordinate system.
     * Defined in the header file so they can be used in a switch statement.
     * @see Paint   For a discussion about static class members in switch
     *              statements.
     */
    static const int OPENGL_COORDINATE_SYSTEM        = 0;
    static const int MATH_COORDINATE_SYSTEM          = 1;
    static const int LEFT_OPENGL_COORDINATE_SYSTEM   = 2;
    static const int ENGINEER_COORDINATE_SYSTEM      = 3;
    static const int MAC_COORDINATE_SYSTEM           = 4;


    /**
     * Returns the coordinate system referred to by _defaultCoordinateSystem
     */
    static CoordinateSystem * GetDefaultCoordinateSystem();


    static CoordinateSystem * GetCoordinateSystem(const int coordinateSystem);


    /**
     * If a setup object wants to set the default coordinate system for viewers
     * to use upon creation, set it here. The Camera object gets whatever is
     * the default at its creation. Note that changing the default coordinate
     * system will not retroactively change objects that have selected the
     * default system.
     *
     * @param coordinateSystem  A coordinate system constant 
     */
    static void SetDefaultCoordinateSystem(const int coordinateSystem);


protected:
    
    static CoordinateSystem * _defaultCoordinateSystem;
	static bool _reverseZ;


};

}

#endif          // COORDINATESYSTEMFACTORY_H

