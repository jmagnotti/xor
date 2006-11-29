#ifndef MUSEUM_H
#define MUSEUM_H


#include <set>

#include "MuseumLayout.h"
#include "Renderable.h"
#include "Room.h"
#include "Lobby.h"


using namespace std;

/**
 * The museum class is a high level renderable that coordinates the placement
 * of several Room objects. A default lobby is used, unless one is specified.
 */
class Museum : public Renderable
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
	void addRoom(Room *);


	/**
	 * Returns the number of rooms in the museum
	 */
	size_t getSize();


	/**
	 * Returns an iterator to the rooms
	 */
	vector<Room*> getRooms();
		

	/**
	 * Returns whether or not the museum has been compiled
	 */
	bool isCompiled();



	/**
	 * Graphical optimizations for the museum
	 */
	void optimize();


	/**
	 * Renders the museum
	 */
	void render(void);


	/**
	 * Sets the the layout for the musem. The default layout is
	 * Hub & Spoke
	 */
	void setLayout(MuseumLayout *);


	/**
	 * Sets the lobby for the museum. This is the room that connects all the other
	 * rooms together.
	 */
	void setLobby(Lobby *);
	

protected:

	set<Room*>	_rooms;

	Lobby *			_lobby;
	MuseumLayout *	_layout;
	
	bool			_compiled;

};


#endif			// MUSEUM_H
