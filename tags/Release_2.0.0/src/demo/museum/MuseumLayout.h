#ifndef MUSEUMLAYOUT_H
#define MUSEUMLAYOUT_H


#include "Museum.h"
#include "Lobby .h"


/**
 * Abstract parent for layouts
 */
class MuseumLayout
{

public:

    /**
     * Modifies the transforms of the rooms accordingly.
     */
	virtual Lobby * performLayout(Museum * museum);


};

#endif			// MUSEUMLAYOUT_H

