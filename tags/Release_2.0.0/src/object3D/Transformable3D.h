#ifndef TRANSFORMABLE3D_H
#define TRANSFORMABLE3D_H


#include "../transform/Transformable.h"
#include "../transform/Transform.h"
#include "../geometry/Vector3D.h"
#include "../geometry/Dimension3D.h"

#include "Object3D.h"

using namespace std;

namespace XOR {

/**
 * Uses the decorator pattern to dynamically add transform ability to
 * Object3D.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class Transformable3D : public Transformable, public Object3D
{

public:
	
	/**
	 * Explicit Constructor
	 */
	Transformable3D(Object3D * object);
	
	/**
	 * Sends the object's base vector through the entire transform stack to
	 * find its current position. 
	 *
	 * @return	A Vector3D that has been transformed to represent the
	 * Object's position in World Coordinates.
	 */
    Vector3D * getBaseVector();

	/**
	 * Sends the object's dimension through the entire transform stack to
	 * find its current size. 
	 *
	 * @return	A Dimension3D that has been transformed to represent the
	 * Object's size in World Coordinates.
	 */
    Dimension3D * getDimension();

	/**
	 * Overrides the render() method in Object3D to allow for applying the
	 * transforms.
	 */
	void render();

protected:

	/**
	 * Required by Object3D. Does nothing.
	 */
	void renderObject();

private:

	Transformable3D();

	Object3D	* _object3D;
	Dimension3D * _size;
	Vector3D	* _position;
	
};

}

#endif			// TRANSFORMABLE3D_H

