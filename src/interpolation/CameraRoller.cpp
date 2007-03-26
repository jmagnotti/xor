#include "CameraRoller.h"


namespace XOR {

CameraRoller::CameraRoller()
{}
	
	
/*
 * gradually restore roll to zero
 */
void CameraRoller::handleTick()
{
	float roll = Controller::GetInstance()->getCamera()->getRotation(2);
	float rollChange = -(roll/5.0f);
	Controller::GetInstance()->getCamera()->incrementRotation(2, rollChange);
}


/*
 * roll camera based on theta-rotation
 */
void CameraRoller::handleMouseEvent(MouseEvent * event)
{
    if (MouseEvent::MOUSE_MOTION == event->getType())
        handleMouseEvent((MouseMotionEvent*)event);
}

/*
 * roll camera based on theta-rotation
 */
void CameraRoller::handleMouseEvent(MouseMotionEvent * mme)
{
    return ;

    Mouse * mouse = Controller::GetInstance()->getMouse();
	if (mouse->isLeftButtonDown()) {

		// rotate camera
		float xChange = (float)(mouse->getCurrentX() - mouse->getPreviousX()) / 2.0f;
		Controller::GetInstance()->getCamera()->incrementRotation(2, -(xChange));
	}
}


void CameraRoller::handleMouseEvent(MouseClickEvent * mce) 
{}

}

