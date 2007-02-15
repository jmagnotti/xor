#ifndef MOUSEBUTTONDOWN_H 
#define MOUSEBUTTONDOWN_H


#include "MouseClickEvent.h"


namespace XOR {

/**
 * Represents the press of of a mouse button. Most of the functionality is found in the 
 * abstract parent MouseClick
 */
class MouseButtonDown : public MouseClickEvent
{

public:

	/**
	 * Explicit Constructor
	 *
	 * @param x	The x-position of the mouse
	 * @param y	The y-position of the mouse
	 * @param button The button index
	 */
	MouseButtonDown(int x, int y, const int button);


	/**
	 * Returns the value of MOUSE_BUTTON_DOWN
	 */
	const int getType();

};

}

#endif          // MOUSEBUTTONDOWN_H

