#ifndef SPRITE3DLISTENER_H
#define SPRITE3DLISTENER_H


#include "../geometry/Vector3D.h"


namespace XOR {

/**
 * Trying to make collision detection a little easier by specifying an
 * interface to allow objects to be notified when a sprite's position
 * changes. An id is passed in to allow for labelling schemes. This
 * allows for "smarter" narrowing casts. While this is generally not
 * safe, the id field provides a reflection-like safety scheme.
 *
 * @author John Magnotti
 * @version 1.0
 */
class Sprite3DListener
{
	public:

	   	virtual void handlePositionChange(Vector3D * position, int id)=0;
};

}

#endif			// SPRITE3DLISTENER_H

