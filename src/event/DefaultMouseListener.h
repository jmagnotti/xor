#ifndef DEFAULTMOUSELISTENER_H
#define DEFAULTMOUSELISTENER_H


#include "../core/Controller.h"
#include "MouseListener.h"
#include "MouseClickEvent.h"
#include "MouseMotionEvent.h"


namespace XOR {

/**
 * Represents the default mouse behavior. Methods are purposely made virtual to allow
 * people to easily extend this classes behavior.
 */
class DefaultMouseListener : public MouseListener
{

public:
	

	/**
	 * Returns a static instance of the DefaultMouseListener
	 */
	static DefaultMouseListener * GetInstance();


	/**
	 * The controller calls this whenever its MouseMotion
	 * or MouseClick handler is called by GLUT
	 */
	virtual void handleMouseEvent(MouseClickEvent * mce);

	virtual void handleMouseEvent(MouseMotionEvent * mme);

protected:

	DefaultMouseListener();


private:

	static DefaultMouseListener * _defaultMouseListener;

};

}

#endif			// DEFAULTMOUSELISTENER_H

