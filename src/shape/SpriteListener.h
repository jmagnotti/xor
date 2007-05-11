#ifndef SPRITELISTENER_H
#define SPRITELISTENER_H


namespace XOR {

/**
 * Trying to make collision detection a little easier by specifying an
 * interface to allow objects to be notified when a sprite's position
 * changes. An id is passed in to allow for labelling schemes. This
 * allows for "smarter" narrowing casts. While this is generally not
 * safe, the id field provides a reflection like safety scheme.
 *
 * @author John Magnotti
 * @version 1.0
 */
class SpriteListener
{
	public:

	   	void handlePositionChange(Vector3D * newPosition, int id);
};

}

#endif			// SPRITELISTENER_H

