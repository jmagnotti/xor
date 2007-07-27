#include "Picture.h"
#include <vector>

using namespace XOR;
using namespace std;

Picture::Picture(Cube * picture)
{
	// make the cube transformable so we can move it
	// and all of that good stuff
	_cube = new Transformable3D(picture);

	_north = NULL;
	_south = NULL;
	_east = NULL;
	_west = NULL;
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

