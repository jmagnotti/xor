#ifndef MOUSECLICKEVENT_H
#define MOUSECLICKEVENT_H


#include "MouseEvent.h"
#include "../../SDL.h"


namespace XOR {

/**
 * Represents the mouse being clicked
 */
class MouseClickEvent : public MouseEvent
{

public:

    static const int LEFT_MOUSE_BUTTON;
    static const int RIGHT_MOUSE_BUTTON;
    static const int MIDDLE_MOUSE_BUTTON;
    static const int MOUSE_WHEEL_UP;
    static const int MOUSE_WHEEL_DOWN;
    


    /**
     * Returns a button value, LEFT_MOUSE_BUTTON, RIGHT_MOUSE_BUTTON, MIDDLE_MOUSE_BUTTON
     */
	const int * getButton();


    /**
     * Returns a state value, MOUSE_BUTTON_UP, MOUSE_BUTTON_DOWN
     */
	const int * getState();


protected:

    MouseClickEvent();

	const int * _button;
    const int * _state;


};

}

#endif			// MOUSECLICKEVENT_H

