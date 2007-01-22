#ifndef DEFAULTMOUSELISTENER_H
#define DEFAULTMOUSELISTENER_H


#include "../../core/Controller.h"

#include "MouseListener.h"
#include "MouseEvent.h"
#include "MouseMotionEvent.h"
#include "MouseButtonUp.h"
#include "MouseButtonDown.h"


namespace XOR {

/**
 * Represents the default mouse behavior. Methods are purposely made virtual to allow
 * people to easily extend this classes behavior. When you declare yourself as a MouseListener, the
 * default constructor adds itself to the Mouse as a listener.
 * These are the functions that you should extend if you want access to mouse events.
 * if you need the raw SDL event, you should extend MouseListener. These methods have empty implementations
 * so that you don't HAVE to implement them.
 */
class DefaultMouseListener : public MouseListener
{

public:

	/**
	 * Returns a static instance of the DefaultMouseListener
	 */
	static DefaultMouseListener * GetInstance();


    /**
     * This method will be called when a mouse button is pressed
     */
	virtual void handleMouseButtonPressed(MouseButtonDown * mbd);


    /**
     * This method will be called when a mouse button is released
     */
	virtual void handleMouseButtonReleased(MouseButtonUp * mbu);


    /**
     * Thie method will be called when the position of the mouse changes.
     */
	virtual void handleMouseMotion(MouseMotionEvent * mme);


protected:


    /**
     * No need for normies to create DefaultMouseListener
     */
	DefaultMouseListener();


    /**
     * This is called by the Mouse. if you want the raw mouse event, extend MouseListener instead.
     */
	void handleMouseEvent(MouseEvent * me);


private:

	static DefaultMouseListener * _defaultMouseListener;


};

}

#endif			// DEFAULTMOUSELISTENER_H

