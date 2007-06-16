#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H


#include "../../../include/SDL.h"


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

	virtual const int getType()=0;


	//-- GETTERS --//
	int     getXPosition();
	int     getYPosition();

	/**
	 * Returns a string representation of the event.
	 */
	virtual char * toString()=0;


protected:

    int _xpos, _ypos;
	char * _eventString;

};

}

#endif          //MOUSEEVENT_H

