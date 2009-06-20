#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <SDL/SDL_opengl.h>
#include "../geometry/Vector3D.h"
#include "../util/Logger.h"
#include "../geometry/Dimension3D.h"
#include "../geometry/Vector2D.h"
#include "../geometry/Dimension2D.h"

namespace XOR
{

/**
 * Please use these as world state transforms sparingly, since we are trying to belive
 * we are in an OO world. Using one of these will apply to all models rendered
 * after the call. What makes this dangerous is that the user may not be aware
 * of subobjects or other high level objects that may be rendered. See Transformable 
 * for some recommendations on object movement. That is the preferred method 
 * for per-object transformations. 
 * 
 * Do not forget to pop() what you push(), before the end
 * of the render loop. The results of calling pop() when the matrix is
 * already pop(ed) is not always defined. If a parent matrix exists, this
 * matrix will be popped. If a parent matrix doesn't exist, then I don't think
 * it will hurt anything, but I am not sure.  
 * 
 * Danger!!! Be very careful about the number of Transforms in action at any 
 * given time. We have gotten bad results when there are a lot (>700) of 
 * glPushMatrix() calls (each Transform::push() corresponds to a glPush, 
 * but other classes (e.g., Orientation) may incur several calls to 
 * Transform::push inside there push() method).
 *
 * @author John Magnotti
 * @author Michael Lam
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
    virtual void transform(Vector2D * position)=0;

    /**
     * Modifies the given dimension object to reflect
     * the effect of the transform.
     */
    virtual void transform(Dimension3D * size)=0;
    virtual void transform(Dimension2D * size)=0;

};

}

#endif			// TRANSFORM_H

