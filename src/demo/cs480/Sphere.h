#include "../../xor.h"

using namespace XOR;

class Sphere : public Object3D
{

public:

	Sphere(Vector3D * origin, float radius, int vStack, int hStack);

	void renderObject();

	Dimension3D * getDimension();

	Vector3D * getBaseVector();

private: 

	Sphere();

	GLUquadric * _sphere;
	Vector3D * _origin;
	float _radius, _vStack, _hStack;
};


