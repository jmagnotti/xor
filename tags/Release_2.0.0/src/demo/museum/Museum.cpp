#include "Museum.h"


/*
 * Default Constructor
 */
Museum::Museum()
{}


/*
 * Adds a room to the museum
 */
void Museum::addRoom(Object3D * room)
{
    _rooms.push_back(room);
}


/*
 * returns a pointer to the set of rooms
 */
vector<Object3D*>::iterator Museum::getRooms()
{
    return _rooms.begin();
}


/*
 * Returns the size of the set of rooms
 */
int Museum::getSize()
{
    return _rooms.size();
}


Dimension3D * Museum::getDimension()
{
	return new Dimension3D(1,1,1);
}


Vector3D * Museum::getBaseVector()
{
	return new Vector3D(0,0,0);
}


void Museum::renderObject()
{
	for(int i=0; i<_rooms.size(); i++)
		_rooms[i]->render();
}

