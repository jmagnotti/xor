#ifndef GLPENDULUM_H
#define GLPENDULUM_H

#include "../../../xor.h"
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <vector>

using namespace XOR;
using namespace std;

class GLPendulum : public Sprite3D
{
public:
	GLPendulum(float length, Vector3D* base, vector<float> thetas);
	~GLPendulum();
	void renderObject();
	void endFrame();
	void updatePosition();
	void buildTrace();
	Vector3D* getBaseVector();
	Dimension3D* getDimension();
	
private:
	float _length;
	float _theta;
	vector<float> _thetas;
	vector<Vector3D*> _tracePoints;
	vector<float>::iterator _currentTheta;
	Vector3D* _base;
	GLUquadric* _bob;
	GLUquadric* _string;
};
#endif
