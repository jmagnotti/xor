#include "Transformable.h"

namespace XOR {

Transformable::Transformable(Object3D * obj)
{
	_object3d = obj;
}

void Transformable::addTransform(Transform * transform)
{
	_transforms.push_back(transform);
}

void Transformable::removeTransform(Transform * transform)
{
	vector<Transform*>::iterator iter = find(_transforms.begin(), _transforms.end(), transform);

	if (iter != _transforms.end())
		_transforms.erase(iter);
}

void Transformable::render()
{
	doTransform();
		renderObject();
	undoTransform();
}

void Transformable::doInverseTransform()
{
	return;

	vector<Transform*>::iterator iter = _transforms.begin();

	while (iter != _transforms.end()) { 
		(*iter)->pushInverse();
		++iter;
	}
}

void Transformable::doTransform()
{

	vector<Transform*>::iterator iter = _transforms.begin();

	while (iter != _transforms.end()) { 
		(*iter)->push();
		++iter;
	}
}

void Transformable::undoTransform()
{

	vector<Transform*>::iterator iter = _transforms.begin();

	while (iter != _transforms.end()) { 
		(*iter)->pop();
		++iter;
	}
}

Dimension3D * Transformable::getDimension()
{
	_dimension = _object3d->getDimension();

	vector<Transform*>::iterator iter = _transforms.begin();

	while (iter != _transforms.end()) { 
		(*iter)->transform(_dimension);
		++iter;
	}

	return _dimension;
}

Vector3D * Transformable::getBaseVector()
{
	_baseVector = _object3d->getBaseVector();
	
	vector<Transform*>::iterator iter = _transforms.begin();

	while (iter != _transforms.end()) { 
		(*iter)->transform(_baseVector);
		++iter;
	}

	return _baseVector;
}

void Transformable::renderObject()
{
    _object3d->render();
}

Transformable::Transformable()
{}

}

