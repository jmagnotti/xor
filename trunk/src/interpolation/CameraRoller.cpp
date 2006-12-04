#include "CameraRoller.h"


namespace XOR {

CameraRoller::CameraRoller()
{}
	
	
/*
 * gradually restore roll to zero
 */
void CameraRoller::handleTick()
{
	float roll = Controller::GetInstance()->getViewer()->getOrientation()->getRotation(2);
	float rollChange = -(roll/5.0f);
	Controller::GetInstance()->getViewer()->getOrientation()->incrementRotation(2, rollChange);
}


/*
 * roll camera based on theta-rotation
 */
void CameraRoller::handleMouseEvent(MouseEvent * event)
{
}

/*
 * roll camera based on theta-rotation
 */
void CameraRoller::handleMouseEvent(MouseMotionEvent * mme)
{
	if (false)
           // Mouse::GetInstance()->getLeftDown())
	{
		// rotate camera
		float xChange = 1.0;//(float)(Mouse::GetInstance()->getCurrentX() - Mouse::GetInstance()->getPreviousX()) / 2.0f;
		Controller::GetInstance()->getViewer()->getOrientation()->incrementRotation(2, -(xChange));
	}
}


void CameraRoller::handleMouseEvent(MouseClickEvent * mce) 
{}

}

