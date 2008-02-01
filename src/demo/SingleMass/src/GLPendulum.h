#ifndef GLPENDULUM_H
#define GLPENDULUM_H

#include "../../../xor.h"
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace XOR;
using namespace std;

class GLPendulum : public Sprite3D
{
public:
	GLPendulum(float length, Vector3D* base, vector<double> thetas);
	~GLPendulum();
	void renderObject();
	void endFrame();
	Vector3D* getBaseVector();
	Dimension3D* getDimension();
	String2D* getThetaString();
	void drawTrace();
	
private:
	//our two vectors
	vector<double> _thetas; //in degrees
	vector<Vector3D*> _tracePoints;
	
	//other class attributes
	float _length;
	float _theta;
	unsigned int _currentTheta;
	String2D* _currentThetaString;
	Vector3D* _base;
	Vector3D* _lastTracePoint;
	GLUquadric* _bob;
	GLUquadric* _string;
};
#endif
