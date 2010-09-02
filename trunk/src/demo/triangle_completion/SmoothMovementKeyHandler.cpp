#include "SmoothMovementKeyHandler.h"

SmoothMovementKeyHandler::SmoothMovementKeyHandler()
{
	_wDown = _sDown = false;
	_distance = 1.0f;
}

SmoothMovementKeyHandler::SmoothMovementKeyHandler(float distance)
{
	_distance = distance;
}

SmoothMovementKeyHandler::~SmoothMovementKeyHandler()
{
	// for now let's be responsible and stopMovingAlongFocalVector
	Controller::GetInstance()->getCamera()->getOrientation()->stopMovingAlongFocalVector();
}

void SmoothMovementKeyHandler::handleKeyDown(KeyDownEvent *kde)
{
	if (kde->getKey() == SDLK_w) {
		if (!_sDown)
			Controller::GetInstance()->getCamera()->getOrientation()->startMovingAlongFocalVector(_distance);
		_wDown = true;
	}
	else if (kde->getKey() == SDLK_s) {
		if (!_wDown)
			Controller::GetInstance()->getCamera()->getOrientation()->startMovingAlongFocalVector(-_distance);
		_sDown = true;
	}
	else {
		DefaultKeyboardListener::handleKeyDown(kde);
	}
}
void SmoothMovementKeyHandler::handleKeyUp(KeyUpEvent * kue)
{
	if (kue->getKey() == SDLK_w) {
		Controller::GetInstance()->getCamera()->getOrientation()->stopMovingAlongFocalVector();

		if (_sDown) // both keys were down, now only s is
			Controller::GetInstance()->getCamera()->getOrientation()->startMovingAlongFocalVector(-_distance);

		_wDown = false;
	}
	else if (kue->getKey() == SDLK_s) {
		Controller::GetInstance()->getCamera()->getOrientation()->stopMovingAlongFocalVector();

		if (_wDown) // both keys were down, now only w is
			Controller::GetInstance()->getCamera()->getOrientation()->startMovingAlongFocalVector(_distance);

		_sDown = false;
	}
	else {
		DefaultKeyboardListener::handleKeyUp(kue);
	}
}
