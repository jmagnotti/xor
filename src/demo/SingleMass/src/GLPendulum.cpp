#include "GLPendulum.h"

namespace GLPendulumConstants
{
	const double PI = 3.1415926535;

	const int WEIGHT_DETAIL = 50;
	const int STRING_DETAIL = 25;
	const int NAIL_DETAIL = 25;

	GLfloat brassAmbient[] = {0.329412f, 0.223529f, 0.027451f, 1.0};
	GLfloat brassDiffuse[] = {0.780392f, 0.568627f, 0.113725f, 1.0};
	GLfloat brassSpecular[] = {0.992157f, 0.941176f, 0.807843f, 1.0};
	GLfloat brassShininess = 0.21794872f * 128.0f;
}

using namespace GLPendulumConstants;

/**
 * Explicit Constructor
 */
GLPendulum::GLPendulum(float length, Vector3D* base) : _length(length), _showArrows(false), _drawnLength(0), _label(NULL)
{
	// Initialize quadric objects
   	weightQuadric = gluNewQuadric();
	stringQuadric = gluNewQuadric();
	nailQuadric = gluNewQuadric();
	
	_base = base;
}

/**
 * Destructor
 */
GLPendulum::~GLPendulum()
{
	// Destroy quadric objects
	gluDeleteQuadric(weightQuadric);
	gluDeleteQuadric(stringQuadric);
	gluDeleteQuadric(nailQuadric);
}

/**
 * Returns the toggle of the arrows
 */
bool GLPendulum::arrowsEnabled()
{
	return _showArrows;
}

/**
 * Toggles the arrows on or off
 */
void GLPendulum::setArrowsEnabled(bool arrowsEnabled)
{
	_showArrows = arrowsEnabled;
}

/**
 * Returns the draw length of the pendulum
 */
float GLPendulum::getDrawnLength()
{
	return _drawnLength;
}

/**
 * Sets the draw length of the pendulum
 */
void GLPendulum::setDrawnLength(float length)
{
	_drawnLength = length;
}

/**
 * Returns the label of the pendulum
 */
char* GLPendulum::getLabel()
{
	return _label;
}

/**
 * Sets the lable of the pendulum
 */
void GLPendulum::setLabel(char* newLabel)
{
	_label = newLabel;
}

/**
 * Return the base vector of the pendulum
 */
Vector3D* GLPendulum::getBaseVector()
{
	Vector3D* tmp = _base;
	return tmp;
}

void GLPendulum::renderObject()
{
	//float thetaInDegrees;
	float weightZ;

	// Set up
 	//thetaInDegrees = (180.0 * theta) / PI;

	// Calculate weightZ
	if (_drawnLength > 0)
		weightZ = -1.0 * _drawnLength;
	else
		weightZ = -1.0 * _length;

	// Set materials for 3D objects
	glMaterialfv(GL_FRONT, GL_AMBIENT, brassAmbient);
   	glMaterialfv(GL_FRONT, GL_DIFFUSE, brassDiffuse);
   	glMaterialfv(GL_FRONT, GL_SPECULAR, brassSpecular);
   	glMaterialf(GL_FRONT, GL_SHININESS, brassShininess);
   		
 	// Draw the pendulum
 	glMatrixMode(GL_MODELVIEW);

 	glPushMatrix();
	{
   		//glRotatef(thetaInDegrees, 0, 0, 1);   
		
		glEnable(GL_LIGHTING);
   		gluSphere(nailQuadric, _length * 0.015, NAIL_DETAIL, NAIL_DETAIL);
		glDisable(GL_LIGHTING);

   		glTranslatef(0, weightZ, 0);
 
		// if (_showArrows)
		// 		{
		// 			glEnable(GL_BLEND);
		// 			glDisable(GL_DEPTH_TEST);
		// 			
		// 			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// 			glColor4f(0.9f, 0, 0.1f, 0.5f);
		// 			drawArrow(0.05f, theta * 0.1);
		// 			glColor4f(0.1f, 0, 0.9f, 0.5f);
		// 			drawArrow(0.05f, theta * 0.1);
		// 			
		// 			glEnable(GL_DEPTH_TEST);
		// 			glDisable(GL_BLEND);
		// 		}
		
		if (_label != NULL)
		{
			glColor4f(0.9f, 0.0f, 0.1f, 1.0f);
		}

   		glEnable(GL_LIGHTING);

   		gluSphere(weightQuadric, _length * 0.1, WEIGHT_DETAIL, WEIGHT_DETAIL);
	
		glRotatef(-90.0, 1.0, 0, 0);
	
		gluCylinder(stringQuadric,
			    0.01 * _length,
			    0.01 * _length,
			    -1.0 * weightZ,
			    STRING_DETAIL,
			    STRING_DETAIL);

   		glDisable(GL_LIGHTING);

	}
   	glPopMatrix();
}

void GLPendulum::drawArrow(float width, float length)
{
   float lineLength;

   if (length < 0)
	lineLength = length + 0.05f;
   else
	lineLength = length - 0.05f;

   // Draw the "line" of the arrow
   glBegin(GL_QUADS);
   {
      glVertex3f(0, width / 2.0f, 0);
      glVertex3f(0, width / -2.0f, 0);
      glVertex3f(lineLength, width / -2.0f, 0);
      glVertex3f(lineLength, width / 2.0f, 0);
   }
   glEnd();

   // Draw the "point" of the arrow
   glBegin(GL_TRIANGLES);
   {
      glVertex3f(lineLength, width / 2.0f + width / 4.0f, 0); 
      glVertex3f(lineLength, width / -2.0f - width / 4.0f, 0);
      glVertex3f(length, 0, 0);
   }
   glEnd();
}
