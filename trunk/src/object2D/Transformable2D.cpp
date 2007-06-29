#include "Transformable2D.h"

namespace XOR {

Transformable2D::Transformable2D(Object2D * object)
{
	_object2D = object;
}

void Transformable2D::render()
{
	push2DState();
		doTransform();
			_object2D->renderObject();
		undoTransform();
	pop2DState();
}

Dimension2D * Transformable2D::getDimension()
{
	_size = _object2D->getDimension();

	vector<Transform*>::iterator iter = _transforms.begin();

	while (iter != _transforms.end()) { 
		(*iter)->transform(_size);
		++iter;
	}

	return _size;
}

Vector2D * Transformable2D::getBaseVector()
{
	_position = _object2D->getBaseVector();
	
	vector<Transform*>::iterator iter = _transforms.begin();

	while (iter != _transforms.end()) { 
		(*iter)->transform(_position);
		++iter;
	}

	return _position;
}

Transformable2D::Transformable2D()
{}

void Transformable2D::renderObject()
{}

}

