#ifndef COMPILEDOBJECT3D_H
#define COMPILEDOBJECT3D_H


#include "../../include/SDL_opengl.h"
#include "Object3D.h"


using namespace std;

namespace XOR {

/**
 * Used to give compilation ability to renderables. The compilation occurs at
 * implicitly at construction. Follows the GOF Decorator Pattern. Note that
 * once an object has been decorated, all interaction should be through the
 * outer layer (the CompiledObject3D). For now the underlying object is still
 * going to exist, but later implementations may delete the object immediately
 * after display list creation, and just store dimension and origin data
 * separately since it would be much more efficient.
 *
 * Because CompiledObject3D still inherits from Transformable, transforms can
 * still be applied. These transforms will be effectively concatenated with the
 * Transforms from the underlying Object3D. Once an Object3D has been compiled,
 * only the Transforms associated with the CompiledObject3D can be manipulated,
 * the Transforms associated with the underlying Object3D have been effectively
 * burned in.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class CompiledObject3D : public Object3D
{

public:

	/**
	 * Destroys the inner object as well.
	 */
	virtual ~CompiledObject3D();


	/**
	 * Explicit Constructor. Performs initial compilation on the object.
	 * @param object	The object to compile and render.
	 * @param store		Whether a reference to the object should be stored
	 * 					after compilation, defaults to true.
	 */
	CompiledObject3D(Object3D * object);
	CompiledObject3D(Object3D * object, bool store);	


	/**
	 * Deletes the underlying Object3D. This should be used to save memory.
	 * Right now it does nothing, because we need to consider getDimension and
	 * getOrigin a bit more.
	 */
	void clean();


	/**
	 * Calls the display list for the underlying renderable
	 * @overrides Render from Object3D
	 */
	void render();



	/**
	 * delegates to the underlying renderable
	 */
	Dimension3D * getDimension();


	/**
	 * delegates to the underlying renderable
	 */
	Vector3D * getBaseVector();

protected:

	/**
	 * Does nothing
	 */
	void renderObject();


private:

	/**
	 * Only makes sense to create with the Object3D.
	 */
	CompiledObject3D();


	/**
	 * Use this method to force compilation of the object. If the object has
	 * been removed, this method will not disturb _displayListID.
	 */
	void compile();


	GLuint _displayListID;

	Object3D * _object3D;

};


}

#endif			// COMPILEDOBJECT3D_H

