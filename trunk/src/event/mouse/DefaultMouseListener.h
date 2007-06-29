#ifndef DEFAULTMOUSELISTENER_H
#define DEFAULTMOUSELISTENER_H


#include "../../core/Controller.h"

#include "../../interpolation/TimedInterpolation.h"
#include "../../core/Controller.h"

#include "MouseListener.h"
#include "MouseEvent.h"
#include "MouseMotionEvent.h"
#include "MouseButtonUp.h"
#include "MouseButtonDown.h"
#include "Mouse.h"


namespace XOR {

class Mouse;

/**
 * TODO Describe the differences between DML and just ML
 */
class DefaultMouseListener : public MouseListener
{

public:

    /**
	 * Constructor
     */
	DefaultMouseListener();


    /**
	 * This method will be called when a mouse button is pressed. It's
	 * implementation is empty.
     */
	virtual void handleMouseButtonPressed(MouseButtonDown * mbd);


    /**
	 * This method will be called when a mouse button is released It's
	 * implementation is empty.
     */
	virtual void handleMouseButtonReleased(MouseButtonUp * mbu);


    /**
	 * Thie method will be called when the position of the mouse changes. If
	 * left mouse button is pressed during a mouse move, the view of the screen
	 * is moved accordingly.
     */
	virtual void handleMouseMotion(MouseMotionEvent * mme);


    /**
	 * Receives the mouse event from the mouse. This method directs the event
	 * to appropriate handle method above.
	 *
	 * @param me An unspecified MouseEvent
     */
	virtual void handleMouseEvent(MouseEvent * me);

};

}

#endif			// DEFAULTMOUSELISTENER_H

