#ifndef MOUSEBUTTONUP_H 
#define MOUSEBUTTONUP_H


#include "MouseClickEvent.h"


namespace XOR {

/**
 * Represents the relase of of a mouse press. Most of the functionality is found in the 
 * abstract parent MouseClick
 */
class MouseButtonUp : public MouseClickEvent
{

public:

	/**
	 * Explicit Constructor
	 *
	 * @param x	The x-position of the mouse
	 * @param y	The y-position of the mouse
	 * @param button The button index
	 */
    MouseButtonUp(int x, int y, const int button);


	/**
	 * Returns the value of MOUSE_BUTTON_UP
	 */
    const int getType();

};

}

#endif          // MOUSEBUTTONUP_H

