#ifndef OBJECT2D_H
#define OBJECT2D_H


#include "../../include/SDL_opengl.h"
#include "../core/Controller.h"
#include "../core/Viewer.h"

namespace XOR {

/**
 *
 */
class Object2D
{

public:

    /*
	 * Pop attributes used to render in 2D
	 */
	void pop2DState();


    /*
	 * Save state then push attributes needed for 2D rendering
	 */
	void push2DState();

    
	/**
	 * Pushes a 2D state, then calls renderObject, then pops the 2D state. This
	 * transition takes a while, so rendering groups of Object2D should be
	 * preferred to rendering them each individually.
	 */
    void render();


	/**
	 * Does the actual rendering work. Note that this does not ensure 2D state.
	 */
	virtual void renderObject()=0;


protected:

	Object2D();

};

}

#endif			// OBJECT2D_H

