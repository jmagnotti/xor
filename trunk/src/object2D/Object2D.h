#ifndef OBJECT2D_H
#define OBJECT2D_H


#include <SDL/SDL_opengl.h>
#include "../core/Controller.h"
#include "../core/Window.h"
#include "../geometry/Dimension2D.h"
#include "../core/Renderable.h"

namespace XOR {

/**
 *
 */
class Object2D : public Renderable
{

public:


    virtual ~Object2D();

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
     * transition takes more than no time at all, so rendering groups of
     * Object2D should be preferred to rendering them each individually.
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

