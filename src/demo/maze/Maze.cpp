#include "Maze.h"


/*
 * Default Constructor
 */
Maze::Maze()
{
	compiled = false;

	//BehaviorParser * bp	= BehaviorParser::GetInstance("maze.behavior");
	//transforms = bp->parse();
}


/* 
 * Adds a renderable
 */
void Maze::addRenderable(RectangularPrism* rend)
{
	renderables.insert(rend);
}


/*
 * Checks for collisions
 */
bool Maze::checkCollision(Vector3D * position)
{
	bool collision = false;

	set<RectangularPrism*>::iterator iter = renderables.begin();
	set<RectangularPrism*>::iterator finish = renderables.end();
	
	while(!collision && iter != finish) {
		collision = (*iter)->checkCollision(position);
		iter++;
	}

	return collision;
}


/*
 * Compiles the maze into a display list
 */
void Maze::compile()
{
	mazeDL_ID = glGenLists(1);

	glNewList(mazeDL_ID, GL_COMPILE);
		renderObject();
	glEndList();

	compiled = true;
}


/* 
 * sets compiled to false
 */
void Maze::decompile()
{
	compiled = false;
}


/* 
 * returns the ending point
 */
Vector3D * Maze::getFinishingPoint()
{
	return _finish;
}


/* 
 * returns the starting point
 */
Vector3D * Maze::getStartingPoint()
{
	return _start;
}


/* 
 * removes bottom faces
 */
void Maze::optimize()
{
	//get an iterator then loop through the renderables, removing the bottom face
	set<RectangularPrism*>::iterator iter = renderables.begin();
	set<RectangularPrism*>::iterator finish = renderables.end();

	while(iter != finish) {
		//(*iter)->removeFace(RectangularPrism::BOTTOM);
		iter++;
	}

	//generate a display list for the maze
	compile();
}


/* 
 * Removes transforms
 */
void Maze::popTransforms()
{
	vector<Transform*>::iterator iter = transforms.begin();
	vector<Transform*>::iterator finish = transforms.end();

	while(iter != finish) {
		(*iter)->pop();
		iter++;
	}
}


/*
 * applies transforms
 */
void Maze::pushTransforms()
{
	vector<Transform*>::iterator iter = transforms.begin();
	vector<Transform*>::iterator finish = transforms.end();

	while(iter != finish) {
		(*iter)->push();
		iter++;
	}
}


/*
 * Calls render on all of its renderables
 */
void Maze::renderObject(void)
{

	//if (!compiled) {
		//		pushTransforms();

		//get an iterator then loop through the renderables, rendering
		set<RectangularPrism*>::iterator iter = renderables.begin();
		set<RectangularPrism*>::iterator finish = renderables.end();

		while (iter != finish) {	
			(*iter)->render();
			iter++;
		}

		//		popTransforms();
	//} else {
		//glCallList(mazeDL_ID);
	//}

}


/**
 * Sets the finishing position
 */
void Maze::setFinishingPoint(Vector3D * p)
{
	_finish = p;
}


/**
 * Sets the starting position
 */
void Maze::setStartingPoint(Vector3D * p)
{
	_start = p;
}

