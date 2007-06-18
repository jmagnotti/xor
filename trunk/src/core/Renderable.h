#ifndef RENDERABLE_H
#define RENDERABLE_H


namespace XOR {

/**
 * Should be like an interface. Allows for generic treatment of all world
 * objects. This is not confined to simply Visual objects, but rather includes
 * auditory content as well.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class Renderable
{

public:

	/**
	 *
	 */
	virtual void render(void)=0;

};

}

#endif		// RENDERABLE_H

