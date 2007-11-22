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

#include "../../../xor.h"

using namespace XOR;

/**
 * Defines an OpenGL drawable pendulum
 *
 * @version 2.0 - converted for XOR compatibility
 * @author Everette Clemmer
 *
 * @version 1.0
 * @author Seth Fowler
 */
class GLPendulum : public Object3D
{
public:
	/**
	 * Explicit constructor - Takes one argument specifying the length of the rod holding the
	 * pendulum bob.
	 *
	 * @param length - the length of the pendulum
	 */
	GLPendulum(float length, Vector3D* base);
	~GLPendulum();

	bool arrowsEnabled();
	Vector3D* getBaseVector();
	float getDrawnLength();
	char* getLabel();
	void renderObject();
	void setArrowsEnabled(bool arrowsEnabled);
    void setDrawnLength(float length);
	void setLabel(char* newLabel);
	void drawArrow(float width, float length);

	/**
	 * Required for Object3D inheritance but not currently used
	 */
	virtual Dimension3D* getDimension();

	

private:
	GLUquadric* weightQuadric;
	GLUquadric* stringQuadric;
	GLUquadric* nailQuadric;

	bool 		_showArrows;
	float 		_drawnLength;
	float 		_length;
	char* 		_label;
	Vector3D* 	_base;
};

#endif
