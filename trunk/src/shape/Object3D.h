#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "../transform/Transformable.h"
#include "../geometry/Vector3D.h"
#include "../geometry/Dimension3D.h"
#include "../paint/Paint.h"
#include "Renderable.h"


namespace XOR {

/**
 * Represents the combination of Renderable and Transformable.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class Object3D : public Renderable, public Transformable
{

public:

	/**
	 * Returns the dimensions of the object
	 * @return A Dimension3D representing the size of the object.
	 */
	virtual Dimension3D * getDimension()=0;


	/**
	 * Returns the point that identifies where the rendering starts. This is
	 * not guaranteed to be min(x,y,z) although that is usually the case for
	 * quads. 
	 *
	 * @return A Vector3D representing the registration point of the object.
	 */	
	virtual Vector3D * getBaseVector()=0;


	/**
	 * Default implementation of rendering. Pushes Transforms if they are
     * available, calls renderObject, then pops the transforms. Calling classes
     * should always use this method.
	 */
	virtual void render();


    /**
     * Sets the paint object associated with this object. The memory associated
     * with this paint object is wholy owned by the object. If you want to
     * share paint objects between several Object3Ds, then an aggregate type
     * should be used that properly handles the allocation and deallocation of
     * memory.
     */
    virtual void setPaint(Paint * paint);


    /**
     * Returns a clone of the paint associated with this object.
     */
    Paint * getPaint();


	/**
	 * Child classes should perform their drawing in this method.
     * Code here should be strictly limited to either actual drawing calls
     * (e.g., OpenGL), or further delegation. Calculation work should not be
     * done in this method. By adhering to this convention, generating display
     * lists is much cleaner.
	 */
	virtual void renderObject()=0;

    Paint * _paint;

};

}

#endif			// OBJECT3D_H

