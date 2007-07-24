#include "Object3D.h"


namespace XOR {
	
/**
 * Set the paint, then delegate the rendering. Base implementation does nothing special
 */
void Object3D::render()
{
	renderObject();
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
Paint * Object3D::getPaint() const
{
    return _paint;
}

}

