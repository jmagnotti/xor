#ifndef MUSEUM_H
#define MUSEUM_H


#include <vector>

#include "../../xor.h"
//#include "MuseumLayout.h"
#include "Room.h"


using namespace std;
using namespace XOR;

/**
 * The museum class is a high level renderable that coordinates the placement
 * of several Room objects. A default lobby is used, unless one is specified.
 */
class Museum : public Object3D
{

public:


	/**
	 * Default Constructor
	 * Creates an empty museum that will use the Hub & Spoke layout
	 * once rooms are added.
	 */
	Museum();


	/**
	 * Adds a room to the musem
	 */
	void addRoom(Room * room);


	/**
	 * Returns the number of rooms in the museum
	 */
	int getSize();


	/**
	 * Returns an iterator to the rooms
	 */
	vector<Room*>::iterator getRooms();


	/**
	 * Renders the museum
	 */
	void renderObject(void);


	/**
	 * Sets the the layout for the musem. The default layout is
	 * Hub & Spoke
	void setLayout(MuseumLayout * layout);
	 */


	/**
	 * Sets the lobby for the museum. This is the room that connects all the other
	 * rooms together.
	void setLobby(Lobby * lobby);
	 */
	
	Dimension3D * getDimension();
	Vector3D * getBaseVector();

private:

	vector<Room*>	_rooms;

//	Lobby *			_lobby;
	//MuseumLayout *	_layout;

};


#endif			// MUSEUM_H

