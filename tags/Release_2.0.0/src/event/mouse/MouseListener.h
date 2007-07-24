#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H


#include "MouseEvent.h"


namespace XOR {

/**
 * Defines an interface for generic treatment of objects that want to be
 * notified of mouse events. No longer auto-adds the object to the Mouse, look
 * to DefaultMouseListener for this behavior.
 */
class MouseListener
{

public:

    /**
     * Implement this method to receive a high level mouse event.
     * Implement DefaultMouseListener if you want to pick which events to be notified of.
     */
	virtual void handleMouseEvent(MouseEvent * me)=0;


};

}

#endif			// MOUSELISTENER_H

