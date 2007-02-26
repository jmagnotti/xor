#ifndef MACCOORDINATESYSTEM_H
#define MACCOORDINATESYSTEM_H


#include "CoordinateSystem.h"


namespace XOR {

/**
 * Coordinate System that rotates around the Y-AXIS by 180 degrees. This should
 * be used on macintosh systems as the default.
 */
class MacCoordinateSystem : public CoordinateSystem
{

public:

    /**
     * Singleton Accessor
     */
    static MacCoordinateSystem * GetInstance();


    /**
     * removes the transform
     */
    void pop();


    /**
     * Apply the 180 rotation on the Y axis
     */
    void push();


private:

    /**
     * Initialize the Y rotation to 180 degrees.
     */
    MacCoordinateSystem();
    static MacCoordinateSystem * _macCoordinateSystem;

};

}

#endif			// MACCOORDINATESYSTEM_H

