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
    if ( (*(me->getType())) == MouseEvent::MOUSE_BUTTON_DOWN)
        handleMouseButtonPressed((MouseButtonDown*)me);
    else if ((*(me->getType())) == MouseEvent::MOUSE_BUTTON_UP)
        handleMouseButtonReleased((MouseButtonUp*)me);
    else
        handleMouseMotion((MouseMotionEvent*)me);
}


void DefaultMouseListener::handleMouseButtonPressed(MouseButtonDown * mbd)
{}


void DefaultMouseListener::handleMouseButtonReleased(MouseButtonUp * mbu)
{}


/*
 * Receives motion events from the default handler. This method will usually be overriden.
 */
void DefaultMouseListener::handleMouseMotion(MouseMotionEvent * mme)
{
/*	
	cout << "MOUSE X: " << mme->getXPosition() << endl;
	cout << "MOUSE Y: " << mme->getYPosition() << endl;

	cout << "RELATIVE MOUSE X: " << mme->getRelativeXPosition() << endl;
	cout << "RELATIVE MOUSE Y: " << mme->getRelativeYPosition() << endl;

	if (Mouse::GetInstance()->getLeftDown())
	{
		// rotate camera
		float xChange = (float)(Mouse::GetInstance()->getCurrentX() - Mouse::GetInstance()->getPreviousX()) / 2.0f;
		float yChange = (float)(Mouse::GetInstance()->getCurrentY() - Mouse::GetInstance()->getPreviousY()) / 2.0f;
		Controller::GetInstance()->getViewer()->getOrientation()->incrementRotation(0, -xChange);
		Controller::GetInstance()->getViewer()->getOrientation()->incrementRotation(1, -yChange);
		//Controller::GetInstance()->getViewer()->getOrientation()->printDebugInfo();
		//Controller::GetInstance()->getViewer()->getOrientation()->incrementRotation(2, xChange);
	}
*/
}

}

