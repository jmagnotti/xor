#include "UserDrivenState.h"

UserDrivenState * UserDrivenState::_userDrivenState = NULL;

UserDrivenState::UserDrivenState(Experiment * e)
{
	_experiment = e;
	_lastPos = new Vector3D(0,0,0);
}

UserDrivenState * UserDrivenState::GetInstance(Experiment * e)
{
	if (_userDrivenState == NULL)
		_userDrivenState = new UserDrivenState(e);	

	return _userDrivenState;
}

void UserDrivenState::handleKeyEvent(KeyEvent * ke)
{
	//detect 'stop' key
	if (KeyEvent::KEY_DOWN_EVENT == ke->getType() && 
		SDLK_SPACE == ke->getKey()) {

		_experiment->setState(TrialCompletedState::GetInstance(_experiment));
	}
}

void UserDrivenState::handleMouseEvent(MouseEvent * me)
{
	// do nothing
}

void UserDrivenState::enterState()
{
	Controller::GetInstance()->getCamera()->getOrientation()->
		startMovingAlongFocalVector(.14667f);
	Controller::GetInstance()->getCamera()->getOrientation()->addListener(this);


}

int UserDrivenState::handlePositionChange(Vector3D * position)
{
	delete _lastPos;
	_lastPos = position->clone();

	return 0;
}

void UserDrivenState::handleRotationChange(float amount, const Vector3D * axis)
{
}

void UserDrivenState::exitState()
{
	cout << "UDS POS: " << _lastPos->toString();

	Controller::GetInstance()->getCamera()->getOrientation()->removeListener(this);

	//remove the interpolation
	Controller::GetInstance()->getCamera()->getOrientation()->
		stopMovingAlongFocalVector();
}

