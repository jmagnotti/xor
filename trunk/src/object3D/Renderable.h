#ifndef RENDERABLE_H
#define RENDERABLE_H


namespace XOR {

/**
 * Should be like an interface. Allows for generic treatment of all world
 * objects.
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

