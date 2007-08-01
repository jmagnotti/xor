#include "Picture.h"
#include <vector>

using namespace XOR;
using namespace std;

Picture::Picture(Transformable3D * picture)
{
	// make the cube transformable so we can move it
	// and all of that good stuff
	_cube = picture;

	_north = NULL;
	_south = NULL;
	_east = NULL;
	_west = NULL;
}

void Picture::goToDefault(int speed)
{
	_cube->addTransform(Translate::CreateTranslate(_defpos, speed));
}

void Picture::undo()
{
	_cube->addTransform(Translate::CreateTranslate(
				new Vector3D(0,0,-1), 100));
}
/**
 * highlights this picture
 * in this case by translating to the highlight position
 */
void Picture::highlight()
{
	_cube->addTransform(Translate::CreateTranslate(_highlightpos, 100));
}

/**
 * Sets the default position that this picture
 * should revert to.
 */
void Picture::setDefaultPosition(Vector3D * pos)
{
//	if(_defpos != NULL)
//		delete _defpos;
	_defpos = pos;
	calcHighlight(pos);
}

/** 
 * Calculates the highlight position by starting from
 * the vector passed in and moving moving closer to
 * the camera.
 */
void Picture::calcHighlight(Vector3D * start)
{
	// delete the old one
//	if(_highlightpos != NULL) 
//		delete _highlightpos;
/*	_highlightpos = new Vector3D(
			start->getX(),
			start->getY(),
			start->getZ() + 1);*/
	_highlightpos = new Vector3D(0,0,1);
}

/**
 * In order to navigate the pictures easily
 * each picture is going to keep track of 
 * what picture is north, south, east, and
 * west of it for easy navigation.  These
 * should be set by an Arrangement.
 */

void Picture::setNorth(Picture * picture)
{
	_north = picture;
}

void Picture::setSouth(Picture * picture)
{
	_south = picture;
}

void Picture::setEast(Picture * picture)
{
	_east = picture;
}

void Picture::setWest(Picture * picture)
{
	_west = picture;
}

Picture * Picture::getNorth()
{
	return _north;
}

Picture * Picture::getSouth()
{
	return _south;
}

Picture * Picture::getEast()
{
	return _east;
}

Picture * Picture::getWest()
{
	return _west;
}

/** 
 * We need to be able to get the transformable3D so
 * we can apply interpolations and all of that good 
 * stuff to them.
 */
Transformable3D * Picture::getTransformable()
{
	return _cube;
}

