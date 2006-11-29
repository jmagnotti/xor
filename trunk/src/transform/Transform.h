#ifndef TRANSFORM_H
#define TRANSFORM_H


#include <stdlib.h>
#include "../../include/SDL_opengl.h"


namespace XOR {

/**
 * Parent for Translate & Rotate
 *
 * Please use these state transforms sparingly, since we are trying to belive we are in an OO world.
 * Using one of these will apply to a model and ALL OF ITS COMPONENTS. 
 * Most renderables (will) implement some mechanism for transforming them. That is the preferred method for
 * per-object transformations.
 * Also, NEVER forget to pop() what you push(), before the end of the rendering loop.
 * All Renderables that have an addTransfrom(...) method perform this already, and the results of calling pop()
 * when the matrix is already pop(ed) is not strictly defined. If a parent matrix exists, this matrix will be popped.
 * If a parent matrix doesn't exist, then I don't think it will hurt anything, but I am not sure.
 */
class Transform
{

public:

	Transform();

	/**
	 * Applies the transform
	 */
	virtual void push(void)=0;


	/**
	 * Removes the transform. Child classes can override this behavior,
	 * but most will just use it. 
	 */
	virtual void pop(void);

};

}

#endif			// TRANSFORM_H

