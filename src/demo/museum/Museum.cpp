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
    _rooms->insert(room);
}


/*
 * returns a pointer to the set of rooms
 */
set<Room*> * Museum::getRooms()
{
    return _rooms;
}


/*
 * Returns the size of the set of rooms
 */
size_t Museum::getSize()
{
    return _rooms->size();
}


/*
 * Returns whether the museum has been compiled
 */
bool Museum::isCompiled()
{
    return  _compiled;
}


/*
 * Sets the layout manager
 */
void Museum::setLayout(MuseumLayout * layout)
{
    _layout = layout;
}


/*
 * Sets the lobby to use for this museum
 */
void Museum::setLobby(Lobby * lobby)
{
    _lobby = lobby;
}

