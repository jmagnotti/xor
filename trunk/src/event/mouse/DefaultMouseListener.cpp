#include "DefaultMouseListener.h"


namespace XOR {

/*
 * Protected Constructor
 */
DefaultMouseListener::DefaultMouseListener()
{}


/*
 * Switch the mouse event to the proper method -- this is the primary function 
 * of the default mouse listener.
 */
void DefaultMouseListener::handleMouseEvent(MouseEvent * me)
{
    cout << "type: " << me->getType() << endl;
    if ( me->getType() == MouseEvent::MOUSE_BUTTON_DOWN) {
        handleMouseButtonPressed((MouseButtonDown*)me);
        cout << "button: " << ((MouseButtonDown*)me)->getButton() << endl;
    }
    else if (me->getType() == MouseEvent::MOUSE_BUTTON_UP)
        handleMouseButtonReleased((MouseButtonUp*)me);
    else
        handleMouseMotion((MouseMotionEvent*)me);
}


/*
 * do nothing on MouseButtonDown
 */
void DefaultMouseListener::handleMouseButtonPressed(MouseButtonDown * mbd)
{}


/*
 * do nothing on MouseButtonUp
 */
void DefaultMouseListener::handleMouseButtonReleased(MouseButtonUp * mbu)
{}


/*
 * Receives motion events from the default handler 
 */
void DefaultMouseListener::handleMouseMotion(MouseMotionEvent * mme)
{
	Mouse * mouse = Controller::GetInstance(NULL)->getMouse();

    cout << "Mouse Event: " << mme->getType() << endl;
    cout << "Mouse button: " << mouse->isLeftButtonDown() << endl;

	// rotate camera
	if (mouse->isLeftButtonDown()) {
		float xChange = - (mme->getRelativeXPosition() / 2.0f);
		float yChange = - (mme->getRelativeYPosition() / 2.0f);

		//FIXME this is relying on Controller already having been constructed.
		//Which is a good bet, but not guaranteed. The empty GetInstance was
		//removed to prevent abuse.
		Controller::GetInstance(NULL)->getViewer()->incrementRotation(Transformable
				::THETA, xChange, new TimedInterpolation(100, NULL));

		Controller::GetInstance(NULL)->getViewer()->incrementRotation(Transformable
				::PHI, yChange, new TimedInterpolation(100, NULL)); }
}

}

