#include "CompiledObject3D.h"


namespace XOR {


/*
 * exp. constr.
 */
CompiledObject3D::CompiledObject3D(Object3D * object, bool store)
{
	_object3D = object;

	compile();

	if (! store)
		clean();
}


/*
 * destructor
 */
CompiledObject3D::~CompiledObject3D()
{
	clean();
}


/*
 * pass-through
 */
Dimension3D * CompiledObject3D::getDimension() const
{
	return _object3D->getDimension();
}


/*
 * pass-through
 */
Vector3D * CompiledObject3D::getOrigin() const
{
	return _object3D->getOrigin();
}


/*
 * compiles the DL
 */ 
void CompiledObject3D::compile()
{
	_displayListID = glGenLists(1);
	glNewList(_displayListID, GL_COMPILE);
		_object3D->render();
	glEndList();	
}


/*
 * call the DL
 */
void CompiledObject3D::render()
{
	push();
		glCallList(_displayListID);
	pop();
}


/*
 * delete the underlying object.
 */
void CompiledObject3D::clean()
{
	/*
	if (_object3D != NULL) {
		delete _object3D;
		// not all implementations automatically set deleted references to
		// NULL, so we do it explicitly
		_object3D = NULL;
	}
	*/
}


}

