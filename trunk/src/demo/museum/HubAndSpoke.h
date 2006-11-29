#ifndef HUBANDSPOKE_H
#define HUBANDSPOKE_H


#include "MuseumLayout.h"


/**
 * A layout that will look like a hub and spokes coming out of it.
 */
class HubAndSpoke : public MuseumLayout
{

public:

	/**
	 * Singleton Accessor
	 */
	static HubAndSpoke * GetInstance(Museum *);


	/**
	 * Performs the layout of the museum, and returns the museum, 
	 * in case different objects are sowing and reaping.
	 */
	Museum * performLayout();


protected:
	
	HubAndSpoke();


private:

	static HubAndSpoke _hubAndSpoke;


};


#endif			// HUBANDSPOKE_H
