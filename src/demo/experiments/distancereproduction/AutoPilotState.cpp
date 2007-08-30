#include "AutoPilotState.h"

AutoPilotState * AutoPilotState::_autoPilotState = NULL;

AutoPilotState::AutoPilotState(Experiment * e)
{
	int interval = Controller::GetInstance()->getTimer()->getInterpolator();

	HIGH_SPEED   = 14.66667/interval/1000.0;
	MID_SPEED    = 10.36667/interval/1000.0;
	LOW_SPEED    = 4.4/interval/1000.0;

	LONG_DISTANCE = 100;
	SHORT_DISTANCE = 60;

	_experiment = e;

	_pairings[0] = new Pair(HIGH_SPEED, SHORT_DISTANCE);
	_pairings[1] = new Pair(HIGH_SPEED, LONG_DISTANCE);

	_pairings[2] = new Pair(MID_SPEED, SHORT_DISTANCE);
	_pairings[3] = new Pair(MID_SPEED, LONG_DISTANCE);

	_pairings[4] = new Pair(LOW_SPEED, SHORT_DISTANCE);
	_pairings[5] = new Pair(LOW_SPEED, LONG_DISTANCE);

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
		startMovingAlongFocalVector(
			_trials[_experiment->getCurrentTrial()]->distance);

	Controller::GetInstance()->getCamera()->getOrientation()->addListener(this);
}

void AutoPilotState::handleTick()
{
	// do nothing
}

int AutoPilotState::handlePositionChange(Vector3D * position)
{
	if (_currentTarget->getZ() >=
			position->getZ()) {
		_experiment->setState(UserDrivenState::GetInstance(
					_experiment->getCurrentTrial(), 
					_trials[_experiment->getCurrentTrial()]->speed));
	}
}

void AutoPilotState::exitState()
{
	//remove the interpolation
	Controller::GetInstance()->getCamera()->getOrientation()->
		stopMovingAlongFocalVector();
}

void AutoPilotState::generateSequence()
{
	SampleWithoutReplacement * swor = new SampleWithoutReplacement(
			0, _pairings.size() - 1, 
			ceil((float)(_experiment->getNumberOfTrials()) / _pairings.size()));

	for (int i=0; i<_experiment->getNumberOfTrials(); i++) {
		_trials.push_back(_pairings[swor->sample()]);
	}
}
