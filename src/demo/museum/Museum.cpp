#include "Museum.h"


/*
 * Default Constructor
 */
Museum::Museum()
{}


/*
 * Adds a room to the museum
 */
void Museum::addRoom(Room * room)
{
    _rooms.push_back(room);
}


/*
 * returns a pointer to the set of rooms
 */
vector<Room*>::iterator Museum::getRooms()
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
	return new Dimension3D(0,0,0);
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


/*
 * Sets the layout manager
void Museum::setLayout(MuseumLayout * layout)
{
    _layout = layout;
}

 */

/*
 * Sets the lobby to use for this museum
void Museum::setLobby(Lobby * lobby)
{
    _lobby = lobby;
}

 */
