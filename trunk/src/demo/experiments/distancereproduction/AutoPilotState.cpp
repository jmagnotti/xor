#include "AutoPilotState.h"

AutoPilotState * AutoPilotState::_autoPilotState = NULL;

AutoPilotState::AutoPilotState(Experiment * e)
{
	_experiment = e;
	_trialNumber = 0;
	generateSequence();
}

AutoPilotState * AutoPilotState::GetInstance(Experiment * e)
{
	if (_autoPilotState == NULL)
		_autoPilotState = new AutoPilotState(e);	

	return _autoPilotState;
}

void AutoPilotState::handleKeyEvent(KeyEvent * ke)
{
	// do nothing
}

void AutoPilotState::handleMouseEvent(MouseEvent * me)
{
	// do nothing
}

void AutoPilotState::enterState()
{
	//add the interpolation
	Controller::GetInstance()->getCamera()->getOrientation()->
		startMovingAlongFocalVector(_speeds[_trialNumber]);

	IntervalTimer::GetInstance()->addCallbackListener(this,
			_times[_trialNumber]);
}

void AutoPilotState::handleTick()
{
	//called when the object is in position
	Controller::GetInstance()->getCamera()->getOrientation()->
		stopMovingAlongFocalVector();

	++_trialNumber;

	_experiment->setState(UserDrivenState::GetInstance(_trialNumber,
				_speeds[_trialNumber]));
}

void AutoPilotState::exitState()
{
	//remove the interpolation
}

void AutoPilotState::generateSequence()
{
	// calculate a random sequence of translations for the camera
}
