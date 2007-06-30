#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <vector>
#include <iostream>
#include <stdio.h>

#include "Transform.h"
#include "Translate.h"
#include "Rotate.h"

#include "../geometry/Dimension3D.h"

using namespace std;

namespace XOR {

/**
 * Easy way to have holistic positioning of an object. Should be updated to
 * use Quaternions | Eigenaxes.
 *
 * @author John Magnotti
 * @version 1.1
 */
class Orientation : public Transform
{

public:

	/**
	 * Explicit Constructor
	 */
	Orientation();

	~Orientation();

	Orientation(Translate * position, Rotate * roll, Rotate * theta, Rotate * phi);

	/**
	 * Explicit Constructor
	 */
	Orientation(Translate * position, Vector3D * focalPoint);


	/**
	 * @see Transform
	 */
	void push(void);

    void clone(Orientation * other);

	/**
	 * Returns a new Orientation whose values are equivalent.
	 */
    Orientation * clone();

	/**
	 * Can't push the inverse of an orientation. Invocation does nothing.
	 */
	void pushInverse(void);


	/**
	 * debug transform info
	 */
    void print();


	/**
	 * @see Transform
	 */
	void pop(void);


    /**
     * @see Transform
     */
    void toIdentity(void);


	/**
     * @see Transform
 	 */
	void transform(Vector3D * position);
	void transform(Vector2D * position);


	/**
	 * @see Transform
 	 */
	void transform(Dimension3D * size);
	void transform(Dimension2D * size);


	void moveAlongFocalVector(float distance);

	Vector3D * getPosition();

	void setPosition(Vector3D * position);
	void incrementPosition(Vector3D * position);
	
	float getRoll();
	float getPitch();
	float getYaw();

	void setRoll(float angle);
	void setPitch(float angle);
	void setYaw(float angle);
	
	void incrementRoll(float angle);
	void incrementPitch(float angle);
	void incrementYaw(float angle);

	void setFocalPoint(Vector3D * focalPoint);

	// interpolated transforms
	
	//void setRoll(float angle, int milliseconds);
	//void setPitch(float angle, int milliseconds);
	//void setYaw(float angl, int milliseconds);
	//
	//void incrementRoll(float angle, int milliseconds);
	//void incrementPitch(float angle, int milliseconds);
	//void incrementYaw(float angl, int milliseconds);
	//
	//void setPosition(Vector3D * position, int milliseconds);
	void incrementPosition(Vector3D * position, int milliseconds);
	//void setFocalPoint(Vector3D * focalPoint, int milliseconds);
	
	//float  getFocalDistance();
	//Vector3D * getFocalPoint() const;

private:

	//void updateFocalPoint();

	//void updateFromFocalPoint();

	vector<Rotate*> _pitch;
	vector<Rotate*> _yaw;
	vector<Rotate*> _roll;
	vector<Translate*> _position;

    //Rotate    * _roll, * _theta, * _phi;
    //Translate * _position;

    //Vector3D  * _focalPoint;

    //float _focalDistance;
};

}

#endif          // ORIENTATION_H

