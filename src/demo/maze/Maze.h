#ifndef MAZE_H
#define MAZE_H


#include <set>
#include <vector>

#include "../../xor.h"


using namespace std;
using namespace XOR;

/**
 * A maze is basically a bunch of rectangular prisms. 
 * The maze adds the notion of a starting point and an ending point.
 */
class Maze : public CollisionRenderable {

public:

	/**
	 * Default Constructor
	 */
	Maze();


	/**
	 * Adds a RectangularPrism to the maze.
	 */
	void addRenderable(RectangularPrism*);


	/*
	 * Returns whether or not the point intersects or is contained by a 
	 * cube with a wall. By doing collision detection holistically, the 
	 * chance of "jump past" errors is reduced.
	 * Adding "sectors" to the maze will allow for greatly reduced collision detection
	 */
	bool checkCollision(Point3D*);


	/**
	 * Creates a display list. The list is then used when render() is called
	 */
	void compile();


	/**
	 * Sets compiled to false.
	 * Can be used to test performance gains from compilation
	 */
	void decompile();


	/**
	 * Returns the end point of the maze
	 */
	Point3D * getFinishingPoint();


	/**
	 * Gets the starting point for the maze
	 */
	Point3D * getStartingPoint();


	/**
	 * Returns the transform vector. Implemented so that when the world object wraps it, the world object can 
	 * subsume them. That way everyone else gets the transforms as well. Note: This would not be desired on all
	 * objects, except for World-esque ones.
	 */
	vector<Transform*> getTransforms();


	/**
	 * HARD CODED SIZE METHOD
	 * this is really bad...
	 */
	int getSize()
	{
		return 52;
	}


	/**
	 * Returns if the maze is compiled
	 */
	bool isCompiled()
	{
		return compiled;
	}


	/**
	 * Removes the bottoms from the rectprisms of the maze, since we don't need
	 * them. Also calls compile to regenerate the display since the rectprisms have changed
	 */
	void optimize();


	/**
	 * Performs transforms then renders
	 */
	void render(void);


	/**
	 * Sets the ending point for the maze. The framework doesn't do anything with this value, but listeners should check
	 * this to enable special events to happen when the player gets to the end of the maze, or closer | further.
	 * By default, the ending point is NULL
	 */
	void setFinishingPoint(Point3D *);


	/**
	 * Sets the starting point for the maze. This is used to determine the translation to be applied at World creation
	 * By default, the starting point is 0,0,0
	 */
	void setStartingPoint(Point3D *);


protected:

	bool compiled;
	int rowSize;
	GLuint mazeDL_ID;
	
	/**
	 * A collection of rectangular prisms that make up the walls of the maze. Note that we are purposely using
	 * a non-ordered collection
	 */
	set<RectangularPrism *> renderables;

	/**
	 * A collectin of transform objects that will allow us to mainpulate the maze as a whole. Order of application
	 * is important, so a vector is used
	 */
	vector<Transform*> transforms;
	
	/**
	 * These points describe the initial and final positions of the maze. A MazeViewer may use this information
	 * to display interesting things
	 */
	Point3D * _start, * _finish;


	/**
	 * Removes the transforms
	 */
	void popTransforms();


	/**
	 * Applies the transforms
	 */
	void pushTransforms();

};


#endif				// MAZE_H
