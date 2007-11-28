#ifndef GLPENDULUM_H
#define GLPENDULUM_H

#include "../../../xor.h"

using namespace XOR;

class GLPendulum : public Object3D
{
public:
	GLPendulum(float length, Vector3D* base);
	~GLPendulum();
	void renderObject();
	Vector3D* getBaseVector();
	
	//unused but required for Object3D inheritance
	Dimension3D* getDimension();
	
private:
	Vector3D* _base;
	float _length;
};
#endif
