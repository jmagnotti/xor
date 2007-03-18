#ifndef HUBANDSPOKE_H
#define HUBANDSPOKE_H


#include "MuseumLayout.h"
#include "Lobby.h"


/**
 * A layout that will look like a hub and spokes coming out of it.
 */
class HubAndSpoke : public MuseumLayout
{

public:

	/**
	 * Singleton Accessor
	 */
	static HubAndSpoke * GetInstance()


	/**
     * Performs the layout of the museum, and returns the Lobby object which
     * will render all the rooms accordingly.
	 */
	Lobby * performLayout(Museum * museum);


private:

	HubAndSpoke();
    
	static HubAndSpoke _hubAndSpoke;
    
    Museum * _museum;

};

#endif			// HUBANDSPOKE_H

