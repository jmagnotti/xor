#ifndef LEFTOPENGLCOORDINATESYSTEM_H
#define LEFTOPENGLCOORDINATESYSTEM_H


#include "CoordinateSystem.h"
#include "Rotate.h"
#include "Scale.h"


namespace XOR {

class LeftOpenGLCoordinateSystem : public CoordinateSystem
{

public:


    /**
     * Singleton Accessor
     */
    static CoordinateSystem * GetInstance();


protected:

    LeftOpenGLCoordinateSystem();


private:

    static LeftOpenGLCoordinateSystem * _leftOpenGLCoordinateSystem;

};

}

#endif          // LEFTOPENGLCOORDINATESYSTEM_H

