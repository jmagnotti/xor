#include "GLPendulum.h"
#include "stdio.h"

namespace GLPendulumConstants
{
	const double PI = 3.1415926535;

	GLfloat brassAmbient[] 	= {0.329412f, 0.223529f, 0.027451f, 1.0};
	GLfloat brassDiffuse[] 	= {0.780392f, 0.568627f, 0.113725f, 1.0};
	GLfloat brassSpecular[] = {0.992157f, 0.941176f, 0.807843f, 1.0};
	GLfloat brassShininess 	= 0.21794872f * 128.0f;
}

using namespace GLPendulumConstants;

GLPendulum::GLPendulum(float length, Vector3D* base, vector<float> thetas) : _length(length), _base(base), _thetas(thetas)
{
	_bob = gluNewQuadric();
	_string = gluNewQuadric();
	_currentTheta = _thetas.begin();
	_pointsAdvanced = _tracePoints.begin();
	buildTrace();
}

GLPendulum::~GLPendulum()
{
	delete _base;
	gluDeleteQuadric(_bob);
	gluDeleteQuadric(_string);
	
	//delete the points in the trace vector
	vector<Vector3D*>::iterator tmp;
	tmp = _tracePoints.begin();
	while(tmp != _tracePoints.end())
	{
		delete *(tmp);
		tmp++;
	}
}

Vector3D* GLPendulum::getBaseVector()
{
	return _base;
}

Dimension3D* GLPendulum::getDimension()
{
	return NULL; //for now
}

void GLPendulum::updatePosition()
{
	//do nothing for now
}

void GLPendulum::endFrame()
{
	//iterate the vector iterator
	(_currentTheta == _thetas.end()) ? (_currentTheta = _thetas.begin()) : (_currentTheta++);
	(_pointsAdvanced == _tracePoints.end()) ? (_pointsAdvanced = _tracePoints.begin()) : (_pointsAdvanced++);
}

void GLPendulum::buildTrace()
{
	vector<float>::iterator currentTheta;
	float thetaRad;
	
	currentTheta = _thetas.begin();
	
	while(currentTheta != _thetas.end())
	{
		//convert from degrees to rads
		thetaRad = (*(currentTheta) * PI)/180.0f;
		//create a new glvertex and push it onto the trace vector
		_tracePoints.push_back(new Vector3D(_length * sin(thetaRad), _length * cos(thetaRad), 0.0f));
		//increment the iterator
		currentTheta++;
	}
}

void GLPendulum::renderObject()
{
	//get the current theta value
	double theta = (*(_currentTheta) * 180)/PI;
			
	// Set materials for 3D objects
	glMaterialfv(GL_FRONT, GL_AMBIENT, brassAmbient);
   	glMaterialfv(GL_FRONT, GL_DIFFUSE, brassDiffuse);
   	glMaterialfv(GL_FRONT, GL_SPECULAR, brassSpecular);
   	glMaterialf(GL_FRONT, GL_SHININESS, brassShininess);
   		
 	// Draw the pendulum
 	glMatrixMode(GL_MODELVIEW);

 	glPushMatrix();
	{
		//rotate to draw position
   		glRotatef(theta, 0, 0, 1);

		//translate to the bob position
  		glTranslatef(0, -_length, 0);
		
		//set draw color
		glColor3f(1.0f,0.0f,.5);
						
		//draw the bob
   		gluSphere(_bob, 0.1 * _length, 20, 20);
		
		//draw the string
		glRotatef(-90.0, 1.0, 0, 0);
		gluCylinder(_string, 0.01f * _length, 0.01f* _length, _length, 10, 10);
		
		glBegin(GL_POINTS);
			_currentPoint = _tracePoints.begin();
			while(_currentPoint != _pointsAdvanced)
			{
				glVertex3f((*_currentPoint)->getX(), (*_currentPoint)->getY(), (*_currentPoint)->getZ());
				_currentPoint++;
			}
		glEnd();

	}
   	glPopMatrix();		
}