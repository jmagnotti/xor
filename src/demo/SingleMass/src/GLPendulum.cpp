#include "GLPendulum.h"

GLPendulum::GLPendulum(float length, Vector3D* base) : _length(length), _base(base)
{
}

GLPendulum::~GLPendulum()
{
	delete _base;
}

void GLPendulum::renderObject()
{
	
}

Vector3D* GLPendulum::getBaseVector()
{
	return _base;
}

Dimension3D* GLPendulum::getDimension()
{
	return NULL; //for now
}