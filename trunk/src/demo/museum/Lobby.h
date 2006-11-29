#ifndef LOBBY_H
#define LOBBY_H


#include "Room.h"


/**
 * A special room that will contain special features as the become more apparent. One 
 * feature will probably be some type of navigation assistant that will help you get 
 * to the other rooms. This information will be provided it from the museum.
 */
class Lobby : public Room
{
	
public:

	/**
	 * Default Constructor
	 */
	Lobby();


	/**
	 * Explicit Constructor
	 */
	Lobby(RectangularVolume *);


	/**
	 * Sets the navigation pane
	 */
	void setNavigationPane(Renderable*);

protected:

	Renderable * _navigationPane;
};

#endif			// LOBBY_H
