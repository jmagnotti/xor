#ifndef OBJECT2D_H
#define OBJECT2D_H


#include <SDL/SDL_opengl.h>

#include "../core/Controller.h"

// this is needed to get the appropriate sizes for 2D rendering surface
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

	/**
	 * Ensures propogation of delete.
	 */
    virtual ~Object2D();

	/**
	 * Pushes a 2D state, then calls renderObject, then pops the 2D state.
	 * This transition takes more than no time at all, so rendering groups
	 * of Object2D should be preferred to rendering them each individually.
	 */
    void render();

	/**
	 * Does the actual rendering work. Note that this does not ensure 2D
	 * state. Call render() to ensure that {push|pop}2DState are called.
	 * This is left public, however, so that you may render an Object2D
	 * without first pushing 2D state (only do this if you already know 2D
	 * state has been pushed).
	 */
	virtual void renderObject()=0;
	virtual Dimension2D * getDimension()=0;
	virtual Vector2D * getBaseVector()=0;

protected:

    /*
	 * Pop attributes used to render in 2D
	 */
	void pop2DState();

    /*
	 * Save state then push attributes needed for 2D rendering
	 */
	void push2DState();
    
	/**
	 * no need to create Object2D
	 */
	Object2D();

};

}

#endif			// OBJECT2D_H

