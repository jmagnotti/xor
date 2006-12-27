#ifndef MATHCOORDINATESYSTEM_H
#define MATHCOORDINATESYSTEM_H


#include "CoordinateSystem.h"
#include "Rotate.h"


namespace XOR {

class MathCoordinateSystem : public CoordinateSystem  
{

public:


    /**
     * Singleton Accessor
     */
    static CoordinateSystem * GetInstance();


protected:

    MathCoordinateSystem();

private:

    static MathCoordinateSystem * _mathCoordinateSystem;

};

}

#endif          // MATHCOORDINATESYSTEM_H

