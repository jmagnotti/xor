#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H


#include "MouseEvent.h"
#include "Mouse.h"


namespace XOR {

class Mouse;

/**
 * Defines an interface for generic treatment of objects that want to be notified of
 * mouse events
 */
class MouseListener
{

public:


    /**
     * Adds the instance to the mouse for your listening pleasure.
     */
    MouseListener();


    /**
     * Implement this method to receive a high level mouse event.
     * Implement DefaultMouseListener if you want to pick which events to be notified of.
     */
	virtual void handleMouseEvent(MouseEvent *)=0;


};

}

#endif			// MOUSELISTENER_H

