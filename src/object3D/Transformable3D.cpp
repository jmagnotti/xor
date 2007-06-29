#include "Transformable3D.h"

namespace XOR {

Transformable3D::Transformable3D(Object3D * obj)
{
	_object3D = obj;
}

void Transformable3D::render()
{
	doTransform();
		_object3D->render();
	undoTransform();
}

Dimension3D * Transformable3D::getDimension()
{
	_size = _object3D->getDimension();

	vector<Transform*>::iterator iter = _transforms.begin();

	while (iter != _transforms.end()) { 
		(*iter)->transform(_size);
		++iter;
	}

	return _size;
}

Vector3D * Transformable3D::getBaseVector()
{
	_position = _object3D->getBaseVector();
	
	vector<Transform*>::iterator iter = _transforms.begin();

	while (iter != _transforms.end()) { 
		(*iter)->transform(_position);
		++iter;
	}

	return _baseVector;
}

Transformable3D::Transformable3D()
{}


void Transformable3D::renderObject()
{}

}

