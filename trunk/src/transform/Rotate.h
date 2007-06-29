#ifndef ROTATE_H
#define ROTATE_H

#include <vector>
#include <iostream>
#include <stdio.h>

#include "Transform.h"

#include "../geometry/Dimension3D.h"
#include "../geometry/Vector2D.h" 
#include "../geometry/Dimension2D.h"
#include "../interpolation/InterpolationEngine.h"
#include "../util/GraphicsConversionUtility.h"

using namespace std;

namespace XOR {

/**
 * Applies a rotate transform
 */
class Rotate : public Transform
{

public:

	static const Vector3D * ROLL;
	static const Vector3D * PITCH;
	static const Vector3D * YAW;

    /**
     * Default Constructor
     */
    Rotate();
    ~Rotate();


	/**
	 * Explicit Constructors for immediate translations
	 */
	static Rotate * CreateRotate(float angle, const Vector3D * axis);
	static Rotate * CreateRotate(float angle, float x, float y, float z);
	//static Rotate * CreateRotate(float angle, Vector3D * axis, InterpolationAction * action);
	//static Rotate * CreateRotate(float angle, float x, float y, float z, InterpolationAction * action);


	/**
	 * Explicit Constructors for interpolated translations
	 */
	static Rotate * CreateRotate(float angle, const Vector3D * axis, int milliseconds);
	static Rotate * CreateRotate(float angle, float x, float y, float z, int milliseconds);
	//static Rotate * CreateRotate(float angle, Vector3D * axis, int milliseconds, InterpolationAction * action);
	//static Rotate * CreateRotate(float angle, float x, float y, float z, int milliseconds, InterpolationAction * action);



    /**
     * Clones the values from one rotate to another
     */
    void clone(Rotate *);


	/**
	 * Applies the rotation
	 */
	void push(void);


	/**
	 * Applies the reverse rotation
	 */
	void pushInverse(void);
	

    /**
     * reset the rotate to have no effect
     */
    void toIdentity();

	void transform(Vector3D * position);
	void transform(Dimension3D * size);

	void transform(Vector2D * position);
	void transform(Dimension2D * size);

    /**
     * 
     */
    void print();

	//Rotate * createTransformedInstance(Vector3D *point);
	//Rotate * createTransformedInstance(Vector3D *point, int milliseconds);

protected:

    friend class Orientation;

	float	_xCoord, _yCoord, _zCoord;
	float	_angle;

	Rotate(float angle, float x, float y, float z);
	Rotate(float angle, const Vector3D * axis);

    //vector<float*> _values;
    //vector<float> _out;

};

class InterpolatedRotate : public Rotate
{

public:
	
	InterpolatedRotate(float angle, const Vector3D * axis, int milliseconds);
	InterpolatedRotate(float angle, float x, float y, float z, int milliseconds);
	//InterpolatedRotate(float angle, Vector3D * axis, int milliseconds, InterpolationAction * action);
	//InterpolatedRotate(float angle, int x, int y, int z, int milliseconds, InterpolationAction * action);
	
	void push();

	void pushInverse();

private:

	float _step, _target;

	int _remaining;
};

class ImmediateRotate : public Rotate
{

public:

	ImmediateRotate(float angle, const Vector3D * axis);
	
	ImmediateRotate(float angle, float x, float y, float z);

};

}

#endif			// ROTATE_H

