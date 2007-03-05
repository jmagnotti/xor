#include "Object3D.h"


#include <iostream>
using namespace std;

namespace XOR {
	
/**
 * Push the transforms, delegate the rendering, then pop the transforms.
 */
void Object3D::render()
{
	// pushing empty transforms is more expensive than the jump
	if (isTransformed()) {
		push();
			renderObject();
		pop();
	}
	else {
		renderObject();
	}
}


/*
 * set the paint
 */
void Object3D::setPaint(Paint * paint)
{
    _paint = paint;
}


/*
 * return a clone of the paint
 */ 
Paint * Object3D::getPaint()
{
    return _paint->clone();
}

}

