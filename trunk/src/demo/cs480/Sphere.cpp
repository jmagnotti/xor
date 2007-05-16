#include "Sphere.h"


Sphere::Sphere(Vector3D * origin, float radius, int vStack, int hStack)
{
	_origin = origin;
	_radius = radius;
	_vStack = vStack;
	_hStack = hStack;
	setTranslation(_origin);
}

void Sphere::renderObject()
{
	glColor3f(1,1,1);
	glPushMatrix();
	glTranslatef(_origin->getX(), _origin->getY(), _origin->getZ());
	gluSphere(_sphere, _radius, _vStack, _hStack);
	glPopMatrix();
}

Dimension3D * Sphere::getDimension()
{
	return new Dimension3D(_radius);
}

Vector3D * Sphere::getBaseVector()
{
	return _origin;
}
