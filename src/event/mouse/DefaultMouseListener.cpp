#include "DefaultMouseListener.h"


namespace XOR {

DefaultMouseListener * DefaultMouseListener::_defaultMouseListener = 0;


/*
 * Protected Constructor
 */
DefaultMouseListener::DefaultMouseListener()
{}


/*
 * Singleton Accessor
 */
DefaultMouseListener * DefaultMouseListener::GetInstance()
{
	if (_defaultMouseListener == NULL)
		_defaultMouseListener = new DefaultMouseListener();

	return _defaultMouseListener;
}


/*
 * Switch the mouse event to the proper method -- this is the primary function 
 * of the default mouse listener.
 */
void DefaultMouseListener::handleMouseEvent(MouseEvent * me)
{
    if ( me->getType() == MouseEvent::MOUSE_BUTTON_DOWN)
        handleMouseButtonPressed((MouseButtonDown*)me);
    else if (me->getType() == MouseEvent::MOUSE_BUTTON_UP)
        handleMouseButtonReleased((MouseButtonUp*)me);
    else
        handleMouseMotion((MouseMotionEvent*)me);
}


void DefaultMouseListener::handleMouseButtonPressed(MouseButtonDown * mbd)
{}


void DefaultMouseListener::handleMouseButtonReleased(MouseButtonUp * mbu)
{}


/*
 * Receives motion events from the default handler. This method will usually be
 * overriden.
 */
void DefaultMouseListener::handleMouseMotion(MouseMotionEvent * mme)
{
    Mouse * mouse = Controller::GetInstance()->getMouse();

	if (mouse->isLeftButtonDown()) {
		// rotate camera
		float xChange = (float)(mouse->getCurrentX() - mouse->getPreviousX()) / 2.0f;
		float yChange = (float)(mouse->getCurrentY() - mouse->getPreviousY()) / 2.0f;

        Controller::GetInstance()->getViewer()->incrementRotation(
                Positionable::THETA, -xChange);
        Controller::GetInstance()->getViewer()->incrementRotation(
                Positionable::PHI, -yChange);
	}
}

}

