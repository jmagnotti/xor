#include "CameraRoller.h"


namespace XOR {

CameraRoller::CameraRoller()
{}
	
	
/*
 * gradually restore roll to zero
 */
void CameraRoller::handleTick()
{
	float roll = Controller::GetInstance(NULL)->getViewer()->getRotation(2);
	float rollChange = -(roll/5.0f);
	Controller::GetInstance(NULL)->getViewer()->incrementRotation(2, rollChange);
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
	if (false)
	{
		// rotate camera
		float xChange = 1.0;//(float)(Mouse::GetInstance()->getCurrentX() - Mouse::GetInstance()->getPreviousX()) / 2.0f;
		Controller::GetInstance(NULL)->getViewer()->incrementRotation(2, -(xChange));
	}
}


void CameraRoller::handleMouseEvent(MouseClickEvent * mce) 
{}

}

