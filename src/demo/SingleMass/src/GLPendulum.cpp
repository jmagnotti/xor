#include "GLPendulum.h"
#include "stdio.h"

GLPendulum::GLPendulum(float length, Vector3D* base) : _length(length), _base(base)
{
}

GLPendulum::~GLPendulum()
{
	delete _base;
}

void GLPendulum::renderObject()
{
	printf("Rendering Pendulum");
}

Vector3D* GLPendulum::getBaseVector()
{
	return _base;
}

Dimension3D* GLPendulum::getDimension()
{
	return NULL; //for now
}