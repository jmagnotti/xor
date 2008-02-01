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
using namespace std;

GLPendulum::GLPendulum(float length, Vector3D* base, vector<double> thetas)
{
	_length = length;
	_base = base;
	_thetas = thetas;
	_bob = gluNewQuadric();
	_string = gluNewQuadric();
	_currentTheta = 0;
	_currentThetaString = new String2D("Just initializing, shouldn't see this",10,25);
	//_drawTrace = false;
	
	_tracePoints.resize(_thetas.size());
	
	cout << _thetas.size() << endl;
	cout << _tracePoints.size() << endl;
	
	// for(vector<Vector3D*>::iterator itr = _tracePoints.begin(); itr != _tracePoints.end(); itr++)
	// {
	// 	
	// }
}

GLPendulum::~GLPendulum()
{
	delete _base;
	gluDeleteQuadric(_bob);
	gluDeleteQuadric(_string);
	delete _currentThetaString;
	
	//delete the points in the trace vector
	// vector<Vector3D*>::iterator tmp;
	// tmp = _tracePoints.begin();
	// while(tmp != _tracePoints.end())
	// {
	// 	delete *(tmp);
	// 	tmp++;
	// }
}

Vector3D* GLPendulum::getBaseVector()
{
	return _base;
}

Dimension3D* GLPendulum::getDimension()
{
	return NULL; //for now
}

String2D * GLPendulum::getThetaString()
{
	return _currentThetaString;
}

void GLPendulum::endFrame()
{
	if(_currentTheta < _thetas.size())
		_currentTheta++;
	else
		_currentTheta = 0;
}

void GLPendulum::drawTrace()
{
	
}

void GLPendulum::renderObject()
{
	//get the current theta value
	double theta = _thetas[_currentTheta];
	float thetaX = _length*cos(theta);
	float thetaY = _length*sin(theta);
	
	if(_currentTheta < 10)
		_tracePoints[_currentTheta] = new Vector3D(thetaX, thetaY, 0.0f);

	
	//this code converts the theta value into a char* as required for the
	//set text method of String2D. This seems to me to be a major hack and
	//I make no guarantees as to its safety/fitness....it just works for the
	//moment
	std::ostringstream o;
	string str;
	char* cstr;
	
	if(!(o << theta))
	{
		std::cout << "Failed to convert theta to string in GLPendulum render object" << '\n';
		_currentThetaString->setText("Failed to set theta value");
	}
	else
	{
		//TODO need to make this a constant length string for blit to screen
		string str("Current Theta: " + o.str() + " degrees");
		cstr = new char[str.size() + 1];
		strcpy(cstr, str.c_str());
		_currentThetaString->setText(cstr);
	}

	glMaterialfv(GL_FRONT, GL_AMBIENT, brassAmbient);
   	glMaterialfv(GL_FRONT, GL_DIFFUSE, brassDiffuse);
   	glMaterialfv(GL_FRONT, GL_SPECULAR, brassSpecular);
   	glMaterialf(GL_FRONT, GL_SHININESS, brassShininess);
   		
 	// Draw the pendulum
 	glMatrixMode(GL_MODELVIEW);

 	glPushMatrix();
	{
		//at this point 0,0,0 is the position of the center of the bob
		
		glEnable(GL_LIGHTING);
		//rotate to draw position
   		glRotatef(theta, 0, 0, 1);

		//translate to the bob position
  		glTranslatef(0, -_length, 0);
								
		//draw the bob
   		gluSphere(_bob, 0.1 * _length, 20, 20);
		
		//draw the string
		glRotatef(-90.0, 1.0, 0, 0);
		
		gluCylinder(_string, 0.01f * _length, 0.01f* _length, _length, 10, 10);
		
		glDisable(GL_LIGHTING);

		glColor3f(0.0f,1.0f,0.0f);
		
		
	}
   	glPopMatrix();
	
	//if(_drawTrace)
	{
		drawTrace();
	}
}