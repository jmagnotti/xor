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

GLPendulum::GLPendulum(float length, Vector3D* base, vector<double> thetas, bool drawTrace)
{
	_base = base;
	_bob = gluNewQuadric();
	_currentTheta = 0;
	//_currentTracePoint = 0;
	_currentThetaString = new String2D("Just initializing, shouldn't see this",10,25);
	_drawTrace = drawTrace;
	_length = length;
	_string = gluNewQuadric();
	_thetas = thetas;

	// for (int i=0; i<_thetas.size(); i++)
	// {
	// 	_tracePoints.push_back(new Vector3D(_length*cos((double)_thetas[i]),
	// 										_length*sin((double)_thetas[i]),
	// 										0.0f));
	// }
}

GLPendulum::~GLPendulum()
{
	gluDeleteQuadric(_bob);
	gluDeleteQuadric(_string);
	delete _base;
	delete _currentThetaString;
	
	// for(int i = 0; i < _tracePoints.size(); i++)
	// {
	// 	delete _tracePoints[i];
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
	{
		_currentTheta++;
		//_currentTracePoint++;
	}
	else
	{
		_currentTheta = 0;
		//_currentTracePoint = 0;
	}
}

void GLPendulum::drawTrace()
{
	double thetaDeg;
	
	glPushMatrix();
		glBegin(GL_LINE_STRIP);
		{
		   	glRotatef(_thetas[_currentTheta], 0, 0, 1);
			glColor3f(0.0f,1.0f,0.0f);

			for(int i = 0; i < _currentTheta; i++)
			{
				//convert radians to degrees and scale
				thetaDeg = _thetas[i] * (M_PI/180) * 1000;

				glVertex3f( _length*(sin(thetaDeg)),
				 			-_length*(cos(thetaDeg)),
				 			0.0f);
			}
		}
		glEnd();
	glPopMatrix();
}

void GLPendulum::renderObject()
{
	//get the current theta value, convert to degrees and scale
	//otherwise theta is < 1
	double theta = _thetas[_currentTheta] * (M_PI/180) * 1000;
	
	//this code converts the theta value into a char* as required for the
	//set text method of String2D.
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
		
		glEnable(GL_LIGHTING);
		
		//rotate to draw position
	   	glRotatef(theta, 0, 0, 1);
			
		//translate to the bob position
	  	glTranslatef(0, -_length, 0);
		
		//draw the bob
	    gluSphere(_bob, 0.1, 20, 20);
		
		//draw the string
		glRotatef(-90.0, 1.0, 0, 0);
		
		//draw the cylinder
		gluCylinder(_string, 0.01f * _length, 0.01f* _length, _length, 10, 10);
		
		glDisable(GL_LIGHTING);
	}
	glPopMatrix();

	if(_drawTrace)
	{
		//draws a circle of radius _length around the nail positon 0,0,0
		//this is clearly where i need to be drawing, but my numbers are off
		drawTrace();
	}
}