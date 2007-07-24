#include "Transformable.h"

namespace XOR
{

int Transformable::_transformCount = 0;

Transformable::Transformable()
{
}

void Transformable::addTransform(Transform * transform)
{
	_transforms.push_back(transform);
	_transformCount++;
	
	cout << "Added T number: " << _transformCount << endl;
}

void Transformable::removeTransform(Transform * transform)
{
	vector<Transform*>::iterator iter =find(_transforms.begin(),
			_transforms.end(), transform);

	if (iter != _transforms.end())
		_transforms.erase(iter);
}

void Transformable::doInverseTransform()
{
	vector<Transform*>::iterator iter = _transforms.begin();

	while (iter != _transforms.end())
	{
		(*iter)->pushInverse();
		++iter;
	}
}

void Transformable::doTransform()
{
	for (int i=0; i < _transforms.size(); i++)
		_transforms[i]->push();
}

void Transformable::undoTransform()
{
	vector<Transform*>::iterator iter = _transforms.begin();

	while (iter != _transforms.end())
	{
		(*iter)->pop();
		++iter;
	}
}

}

