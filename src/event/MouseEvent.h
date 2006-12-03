#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H


#include "../../include/SDL.h"


namespace XOR {

/**
 * Parent class for mouse events. SDL supports multiple mice (and keyboards), 
 * but that is not needed yet. Still, we should consider having the device index be
 * part of the event, for future compatibility.
 */
class MouseEvent
{

public:

    static const int MOUSE_MOTION; 
    static const int MOUSE_BUTTON_DOWN; 
    static const int MOUSE_BUTTON_UP; 


	/**
	 * Default Constructor
	 */
	MouseEvent();


	//-- GETTERS --//
	int     getXPosition();
	int     getYPosition();

	virtual const int * getType()=0;


protected:

    Uint16  *_xpos, *_ypos;

};

}

#endif          //MOUSEEVENT_H

