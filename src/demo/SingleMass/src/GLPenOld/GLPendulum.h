#ifndef GLPENDULUM_H
#define GLPENDULUM_H

#ifdef __APPLE__
 #include <OpenGL/gl.h>
#else
 #include "GL/gl.h"
#endif

#ifdef __APPLE__
 #include <GLUT/glut.h>
#else
 #include "GL/glut.h"
#endif

#include <stdlib.h>
#include <stdio.h>

#include "../../../xor.h"
using namespace XOR;

/**
 * Defines an OpenGL drawable pendulum
 *
 * all comments placeholders at present
 */
class GLPendulum : public Object3D
{
public:
	/**
	 * Explicit constructor 
	 */
	GLPendulum(float length, Vector3D* base);
	
	/**
	 * Destructor
	 */
	~GLPendulum();

	/**
	 * Arrow toggle
	 */
	bool arrowsEnabled();
	
	/**
	 * Get base vector
	 */
	Vector3D* getBaseVector();
	
	/**
	 * get drawn length
	 */
	float getDrawnLength();
	
	/**
	 * get label
	 */
	char* getLabel();
	
	/**
	 * render object
	 */
	void renderObject();
	
	/**
	 * set arrows
	 */
	void setArrowsEnabled(bool arrowsEnabled);
	
	/**
	 * set draw length
	 */
	    void setDrawnLength(float length);
	
	/**
	 * set label
	 */
	void setLabel(char* newLabel);
	
	/**
	 * draw arrow
	 */
	void drawArrow(float width, float length);
	
	/**
	 * Required for Object3D inheritance but not currently used
	 */
	Dimension3D* getDimension()
	{
		return NULL;
	}

	

private:
	GLUquadric* weightQuadric;
	GLUquadric* stringQuadric;
	GLUquadric* nailQuadric;

	bool 		_showArrows;
	float 		_length;
	char* 		_label;
	Vector3D* 	_base;
};

#endif
