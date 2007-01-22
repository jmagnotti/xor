#ifndef ENGINEERCOORDINATESYSTEM_H
#define ENGINEERCOORDINATESYSTEM_H


#include "CoordinateSystem.h"
#include "Rotate.h"
#include "Scale.h"


namespace XOR {

class EngineerCoordinateSystem : public CoordinateSystem  
{

public:


    /**
     * Singleton Accessor
     */
    static EngineerCoordinateSystem * GetInstance();


protected:

    EngineerCoordinateSystem();

private:

    static EngineerCoordinateSystem * _engineerCoordinateSystem;

};

}

#endif          // ENGINEERCOORDINATESYSTEM_H

