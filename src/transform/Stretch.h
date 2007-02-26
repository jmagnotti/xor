#ifndef STRETCH_H
#define STRETCH_H


#include "Translate.h"
#include "Scale.h"
#include "Transform.h"


namespace XOR {

/**
 *
 */
class Stretch : public Transform
{

public:

	Stretch();
	~Stretch();
	Stretch(Vector3D * origin, Vector3D * stretch);

	void push();
	void pushInverse();
	void pop();
	void clear();

	/**
	 * Easy way to increment a stretch
	 * to decrement, just increment by a negative amount
	 */
    void increment(Vector3D *);
    void increment(Vector3D *, InterpolationEngine * interpolation);

    void set(Vector3D *);
    void set(Vector3D *, InterpolationEngine * interpolation);

	void setOrigin(Vector3D * origin);


	Vector3D * toVector();

private:

	Translate * _translate;
	Scale 	  * _scale;
    char * buffer;

};

}

#endif			// STRETCH_H

