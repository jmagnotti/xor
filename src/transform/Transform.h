#ifndef TRANSFORM_H
#define TRANSFORM_H


#include "../../include/SDL_opengl.h"
#include "../geometry/Vector3D.h"
#include "../geometry/Dimension3D.h"


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
 * already pop(ed) is not always defined. If a parent matrix exists, this
 * matrix will be popped. If a parent matrix doesn't exist, then I don't think
 * it will hurt anything, but I am not sure.  
 *
 * @author John Magnotti
 * @version 1.1
 */
class Transform
{

public:

    Transform();

	/**
	 * Removes the transform from the GL transform stack.
	 */
	virtual void pop(void);


	/**
	 * Applies the transform. This affects all subsequent renderings until
	 * pop() is called;
	 */
	virtual void push(void)=0;


	/**
	 * Applies the inverse of the transform, i.e., the transform T* such that
	 * T(T*) = I; This is very different from pop(), which removes the
	 * transform from the GL transform stack.
	 */
	virtual void pushInverse(void)=0;


    /**
     * Restores the transform to an identity transform.
     * Useful to 'reset' object transforms, without
     * removing the object.
     */
    virtual void toIdentity(void)=0;


	/**
     * Modifies the given Vector to be the position
     * after being transformed.
 	 */
	virtual void transform(Vector3D * position)=0;


	/**
     * Modifies the given dimension object to reflect
     * the effect of the transform.
 	 */
	virtual void transform(Dimension3D * size)=0;

};

}

#endif			// TRANSFORM_H

