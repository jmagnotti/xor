#ifndef SMOOTHMOVEMENTKEYHANDLER_H
#define SMOOTHMOVEMENTKEYHANDLER_H

#include "../../xor.h"

using namespace XOR;

/**
 * Adds continuous movement (via Orientation::startMovingAlongFocalVector()) 
 * while 'w' || 's' are held down. Keys not handled are passed to DefaultKeyboardListener. 
 * Handles multiple presses by storing the pressed state of the keys and giving precedence 
 * to the first key that was pressed. For Example, if while holding down 'w' the user presses 's', 
 * 'w' still has precedent. If 'w' is released before 's' is released, the effect of 's' is applied. 
 * 
 * @usage: Controller::GetInstance()->getKeyboard()->addListener(new SmoothMovementKeyHandler());
 * 
 * @author John Magnotti
 * @version 1.0
 */
class SmoothMovementKeyHandler : public DefaultKeyboardListener
{
public:
	SmoothMovementKeyHandler();
	SmoothMovementKeyHandler(float distance);

	virtual ~SmoothMovementKeyHandler();

	void handleKeyDown(KeyDownEvent * kde);

	void handleKeyUp(KeyUpEvent * kue);

private:
	float _distance;
	bool _wDown, _sDown;
};

#endif			// SMOOTHMOVEMENTKEYHANDLER_H
