#ifndef TRANSFORMABLE2D_H
#define TRANSFORMABLE2D_H


#include "../transform/Transformable.h"
#include "../transform/Transform.h"
#include "../geometry/Vector2D.h"
#include "../geometry/Dimension2D.h"

#include "Object2D.h"
#include <SDL/sdl.h>

using namespace std;

namespace XOR {

/**
 * Uses the decorator pattern to dynamically add transform ability to
 * Object2D.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class Transformable2D : public Transformable, public Object2D
{

public:
	
	/**
	 * Explicit Constructor
	 */
	Transformable2D(Object2D * object);
	
	/**
	 * Sends the object's base vector through the entire transform stack to
	 * find its current position. 
	 *
	 * @return	A Vector2D that has been transformed to represent the
	 * Object's position in World Coordinates.
	 */
    Vector2D * getBaseVector();

	/**
	 * Sends the object's dimension through the entire transform stack to
	 * find its current size. 
	 *
	 * @return	A Dimension2D that has been transformed to represent the
	 * Object's size in World Coordinates.
	 */
    Dimension2D * getDimension();

	/**
	 * Overrides the render() method in Object2D to allow for applying the
	 * transforms.
	 */
	void render();

protected:

	/**
	 * Required by Object2D. Does nothing.
	 */
	void renderObject();

private:

	Transformable2D();

	Object2D	* _object2D;
	Dimension2D * _size;
	Vector2D	* _position;
	
};

}

#endif			// TRANSFORMABLE2D_H

