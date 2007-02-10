#ifndef RENDERABLE_H
#define RENDERABLE_H


#include "../geometry/Dimension3D.h"


namespace XOR {

/**
 * Should be like an interface. Allows for generic treatment of all drawing
 * objects.
 */
class Renderable
{

public:

	/**
	 * Calls the display list for an object. If a list has not been
	 * created, nothing will be drawn. This will only be the case if
	 * isCompiled() is false. When renderables are added to the
	 * World, they are automatically compiled. 
	 */
	virtual void render(void)=0;

};

}

#endif		// RENDERABLE_H

