#ifndef SCALE_H
#define SCALE_H


#include <vector>
#include <stdio.h>
#include <SDL/SDL_opengl.h>

#include "../geometry/Vector3D.h"
#include "../interpolation/InterpolationEngine.h"
#include "Transform.h"


namespace XOR {

/**
 * Performs a Scalar Matrix transform. For each point rendered after the Scalar
 * S(2,4,6) has been pushed, the point will be render at Px*2 Py*4, Pz*6.
 * P(2,3,5) would be rendered at (4,12,30). Note that this is not simply
 * resizing the object (which is the goal of Stretch).  
 *
 * @author John Magnotti, Michael lam
 * @version 1.0
 */
class Scale : public Transform
{

    friend class Transformable;

public:

    virtual ~Scale();

    Scale();

    Scale(float x, float y, float z);

    Scale(Vector3D * scalar);

    void push();

    void pushInverse();

    void clone(Scale * other);

    void set(Vector3D * scale);
    void set(Vector3D * scale, InterpolationEngine * interpolation);

    void increment(Vector3D * scale);
    void increment(Vector3D * scale, InterpolationEngine * interpolation);

    void clear();

	Vector3D * toVector();

    void print();

protected:

	/*
	 * fill the _values vector
	 */
	void fillVector();

    float _xScale, _yScale, _zScale;

    char * buffer;

    vector<float*> _values;
    vector<float>  _out;

};

}

#endif          // SCALE_H

