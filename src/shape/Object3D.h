#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "../transform/Positionable.h"
#include "../geometry/Vector3D.h"
#include "../geometry/Dimension3D.h"
#include "Renderable.h"


namespace XOR {

/**
 * Represents the combination of Renderable and Positionable.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class Object3D : public Renderable, public Positionable
{

public:

	/**
	 * Returns the dimensions of the object
	 * @return A Dimension3D representing the size of the object.
	 */
	virtual Dimension3D * getDimension() const = 0;


	/**
	 * Returns the point that identifies where the rendering starts. This is
	 * not guaranteed to be min(x,y,z) although that is usually the case for
	 * quads. 
	 * @return A Vector3D identifying the rendering origin.
	 */	
	virtual Vector3D * getOrigin() const = 0;


	/**
	 * Code in here should be strictly limited to either delegating further
	 * rendering or drawing (e.g., OpenGL) calls. Calculation work should be
	 * done outside of the this method. By adhering to this convention,
	 * generating display lists is much cleaner.
	 */
	virtual void render()=0;

};

}

#endif			// OBJECT3D_H

