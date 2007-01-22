#ifndef CAMERAROLLER_H
#define CAMERAROLLER_H


#include <iostream>

#include "../core/Controller.h"
#include "../event/timer/Timer.h"

namespace XOR {

/**
 * Applies a rotate transform
 */
class CameraRoller : public TimerListener, public MouseListener
{


public:

	CameraRoller();

	void handleTick();

	void handleMouseEvent(MouseEvent * event);

	void handleMouseEvent(MouseMotionEvent * mme);

	void handleMouseEvent(MouseClickEvent * mce);

};

}

#endif

