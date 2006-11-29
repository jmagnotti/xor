#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H


#include "MouseClickEvent.h"
#include "MouseMotionEvent.h"


namespace XOR {

/**
 * Defines an interface for generic treatment of objects that want to be notified of
 * mouse events
 */
class MouseListener
{

public:

	MouseListener()
    {}

	virtual void handleMouseEvent(MouseClickEvent *)=0;
	virtual void handleMouseEvent(MouseMotionEvent *)=0;

};

}

#endif			// MOUSELISTENER_H

