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

/**
 * A representation of a lit 3D pendulum. Lighting is defined on the objects and 
 * uses a brass color. A trace method toggles the drawing of a continuous line 
 * following the center of the pendulum bob through its motion.
 */
class GLPendulum : public Sprite3D
{
public:
	/**
	* Explicit constructor
	* 
	* Defines a pendulum of length length at origin base. thetas is
	* a double vector containing the angular position of the pendulum
	* bob.
	*
	*@param length - the length of the pendulum
	*@param base - the pendulum origin (nail)
	*@param thetas - the theta values for the simulation
	*/
	GLPendulum(float length, Vector3D* base, vector<double> thetas, bool drawTrace);
	
	/**
	* Destructor
	*/
	~GLPendulum();
	
	/**
	* Method initializes the _tracePoints vector from _thetas
	* will probably be removed in favor of real time calcs when
	* i make the app multithreaded
	*/
	void buildTrace();
	
	/**
	* Required for any sprite 3d object. Called by the sprite handler to
	* render the sprite to the stage
	*/
	void renderObject();
	
	/**
	* Called on frame exit. Performs maintenance by incrementing counters
	* and updating any end of frame variables for the next frame
	*/
	void endFrame();
	
	/**
	* Returns the origin vector of the object
	*
	*@return Vector3D*
	*/
	Vector3D* getBaseVector();
	
	/**
	* Required for object3d which is a parent to sprite
	
	* does nothing at the moment besides return NULL
	*
	*@return Dimension3D*
	*/
	Dimension3D* getDimension();
	
	/**
	* Returns a string representation of the current angular position
	* of the pendulm from the y axis in degrees.
	*
	*@return String2D*
	*/
	String2D* getThetaString();
	
	/**
	* Draws the trace of the pendulum centered on the pendulum bob
	* Still in experimental stages should probably be a boolean toggle
	* that activates an if block in renderObject.
	*/
	void drawTrace();
	
private:
	vector<double> _thetas; //in degrees
	//vector<Vector3D*> _tracePoints;//not sure if this is necessary yet
	
	int _currentTheta;
	//int _currentTracePoint;
	
	//other class attributes
	float _length;
	float _theta;
	bool _drawTrace;
	
	String2D* _currentThetaString;
	Vector3D* _base;
	GLUquadric* _bob;
	GLUquadric* _string;
};
#endif
