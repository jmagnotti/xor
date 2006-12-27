#ifndef TRANSFORM_H
#define TRANSFORM_H


#include <stdlib.h>
#include "../../include/SDL_opengl.h"

#include "../interpolation/Interpolable.h"


namespace XOR {

/**
 * Please use these state transforms sparingly, since we are trying to belive
 * we are in an OO world. Using one of these will apply to all models rendered
 * after the call. What makes this dangerous is that the user may not be aware
 * of subobjects or other high level objects that may be rendered. Most
 * renderables (will) implement some mechanism for transforming them, see
 * Positionable. That is the preferred method for per-object transformations.
 * Also, NEVER forget to pop() what you push(), before the end
 * of the render loop. The results of calling pop() when the matrix is
 * already pop(ed) is not strictly defined. If a parent matrix exists, this
 * matrix will be popped. If a parent matrix doesn't exist, then I don't think
 * it will hurt anything, but I am not sure.  
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class Transform
{

public:

	/**
	 * Applies the transform
	 */
	virtual void push(void)=0;


	/**
	 * Removes the transform.
	 */
	virtual void pop(void);

};

}

#endif			// TRANSFORM_H

