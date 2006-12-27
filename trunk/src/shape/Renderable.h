#ifndef RENDERABLE_H
#define RENDERABLE_H


namespace XOR {

/**
 * Should be like an interface. Allows for generic treatment of all drawing
 * objects.
 */
class Renderable
{

public:

	/**
     * Code in here should be strictly limited to either delegating further
     * rendering or drawing (e.g., OpenGL) calls. Calculation work should be
     * done outside of the this method. By adhering to this convention,
     * generating display lists is much easier.
	 */
	virtual void render(void)=0;


	/**
     * Returns the class type. This should be used by sub-interfaces of
     * renderable to disambiguate themselves. 
	 */
	virtual char * getRenderableType()
	{
		return "RENDERABLE";
	}

};

}

#endif		// RENDERABLE_H

