#ifndef MUSEUM_H
#define MUSEUM_H


#include <vector>

#include "../../xor.h"
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
	void addRoom(Object3D * room);


	/**
	 * Returns the number of rooms in the museum
	 */
	int getSize();


	/**
	 * Returns an iterator to the rooms
	 */
	vector<Object3D*>::iterator getRooms();


	/**
	 * Renders the museum
	 */
	void renderObject(void);


	Dimension3D * getDimension();


	Vector3D * getBaseVector();


private:

	vector<Object3D*>	_rooms;

//	Lobby *			_lobby;
	//MuseumLayout *	_layout;

};


#endif			// MUSEUM_H

