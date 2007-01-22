#ifndef SPECKEYEVENT_H
#define SPECKEYEVENT_H


#include <stdlib.h>


namespace XOR {

/**
 * SpecialKeyEvent.h
 *
 * i.e. PageUp PageDn
 */
class SpecialKeyEvent
{

protected:
	int		cursorX, cursorY;
	int		keyPressed;

public:

	/**
	 * Explicit Constructor
	 *
	 * Constructor without mouse coordinates, uses 0,0
	 */
	SpecialKeyEvent(int key);


	/**
	 * Explicit Constructor
	 *
	 * Special Key event with mouse coordinates
	 */
	SpecialKeyEvent(int key, int xpos, int ypos);

	int getKeyPressed();

};

}

#endif		// SPECKEYEVENT_H

