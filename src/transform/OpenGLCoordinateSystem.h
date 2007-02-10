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
    static OpenGLCoordinateSystem * GetInstance();

    void push();
    void pop();


protected:

    OpenGLCoordinateSystem();


private:

    static OpenGLCoordinateSystem * _openGLCoordinateSystem;

};

}

#endif          // OPENGLCOORDINATESYSTEM_H
