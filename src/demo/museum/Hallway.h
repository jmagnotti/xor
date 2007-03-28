#ifndef HALLWAY_H
#define HALLWAY_H


#include <iostream>
#include "../../xor.h"

using namespace XOR;
using namespace std;

/**
 *
 */
class Hallway : public Object3D
{

public:

    Dimension3D * getDimension(){return NULL;}
    Vector3D * getBaseVector(){return NULL;}


    /**
     * Explicit Constructor.
     *
     * @param start     The registration point of the hallway. Values will be calculated FROM this point.
     * @param startExitVector   Values will be calculated FROM this point. 
     * @param finish    The ending point of the hallway. 
     * @param finishEntranceVector  Values will be calculated TO this point. This
     *                  is useful if the room is tilted at an angle. The calling class has a much
     *                  better idea of a value for this attack vector than the hallway can estimate.
     *                  For example, if you want to finish at [0,0,0] and approach from the front,
     *                  you could specify a finishEntranceVector of [0,0,1]. If you wanted to
     *                  approach from the top, use [0,1,0]
     * @param diameters The amount of space the hallway will occupy in directions
     *                  other than the one it is currently travelling in. For example, if the
     *                  Hallway is connecting [0,0,0] with [0,0,10] the diameters will cause the
     *                  opposing wall to extend from [width, height, 0] to [width, height, 10]. 
     * @param paint     The paint to use on the hallway.
     */
    Hallway(Vector3D * start,  Vector3D * startExitVector, 
            Vector3D * finish, Vector3D * finishEntranceVector, 
            Dimension3D * diameters, Paint * paint);


    /**
     * Constructs a hallway connecting the two rooms' doors. Determines where the
     * finish point is relative to the starting point in order to craft the
     * appropriate route. Hallways never travel in more than one direction at a
     * time. This leads to a bit more rendering work, but makes scripted movement
     * and collision detection much simpler.
     */
    void build();


    /**
     * Renders the hallway 
     */
    void renderObject();


private:

    /**
     * Private default constructor
     */
    Hallway();


	Vector3D * _start,  * _startVector, 
             * _finish, * _finishVector;

	Dimension3D * _diameters;

    Object3DCollection * _renderable;

	Paint * _paint;

};

#endif			// HALLWAY_H

