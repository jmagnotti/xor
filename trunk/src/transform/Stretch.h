#ifndef STRETCH_H
#define STRETCH_H


#include "Translate.h"
#include "Scale.h"
#include "Transform.h"
#include "../geometry/Dimension3D.h"
#include "../geometry/Vector3D.h"


namespace XOR {

/**
 *
 */
class Stretch : public Transform
{

public:

	Stretch();

    /**
     * TODO what does stretch entail ?
     *
     */
	Stretch(Vector3D * origin, Vector3D * stretch);

	~Stretch();

	void push();
	void pushInverse();
	void pop();
	void toIdentity();

    void transform(Vector3D * position);
    void transform(Dimension3D * size);

    void transform(Vector2D * position);
    void transform(Dimension2D * size);

	/**
	 * Easy way to increment a stretch
	 * to decrement, just increment by a negative amount
	 */
	void setOrigin(Vector3D * origin);


	Vector3D * toVector();
private:

	Translate * _translate;
	Scale 	  * _scale;
    char * buffer;

};

}

#endif			// STRETCH_H

