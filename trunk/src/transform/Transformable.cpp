#include "Transformable.h"

namespace XOR {

Transformable::Transformable()
{}

void Transformable::addTransform(Transform * transform)
{
	_transforms.push_back(transform);
}

void Transformable::removeTransform(Transform * transform)
{
	vector<Transform*>::iterator iter = 
		find(_transforms.begin(), _transforms.end(), transform);

	if (iter != _transforms.end())
		_transforms.erase(iter);
}

void Transformable::doInverseTransform()
{
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


}

