#ifndef OPENGLCOORDINATESYSTEM_H
#define OPENGLCOORDINATESYSTEM_H


#include "CoordinateSystem.h"
#include "Rotate.h"


namespace XOR {

class OpenGLCoordinateSystem : public CoordinateSystem
{

public:


    /**
     * Singleton Accessor
     */
    static CoordinateSystem * GetInstance();


protected:

    OpenGLCoordinateSystem();


private:

    static OpenGLCoordinateSystem * _openGLCoordinateSystem;

};

}

#endif          // OPENGLCOORDINATESYSTEM_H

