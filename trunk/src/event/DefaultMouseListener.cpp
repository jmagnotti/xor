#include "DefaultMouseListener.h"

namespace XOR {

DefaultMouseListener* DefaultMouseListener::_defaultMouseListener = 0;


/*
 * Protected Constructor
 */
DefaultMouseListener::DefaultMouseListener()
{

}


/*
 * Singleton Accessor
 */
DefaultMouseListener* DefaultMouseListener::GetInstance()
{
	if (_defaultMouseListener == NULL)
		_defaultMouseListener = new DefaultMouseListener();

	return _defaultMouseListener;
}


/* 
 * Responds to mouse events
 */
void DefaultMouseListener::handleMouseEvent(MouseClickEvent* mce)
{
	//cout << "MOUSE START X: " << mce->getXPosition() << endl;
	//cout << "MOUSE START Y: " << mce->getYPosition() << endl;

	//dxdir = (mouseCurrentX - mouseStartX)/150.0;
	//dydir = (mouseCurrentY - mouseStartY)/150.0;

	//xdir += dxdir;
	//ydir += dydir;

	//glRotatef(ydir, 1, 0, 0);
	//glRotatef(xdir, 0, 1, 0);
}


void DefaultMouseListener::handleMouseEvent(MouseMotionEvent* mme)
{
	//cout << "MOUSE X: " << mme->getXPosition() << endl;
	//cout << "MOUSE Y: " << mme->getYPosition() << endl;

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
}

}

