#include "AutoPilotState.h"

Pair::Pair(float speed, int distance)
{
	this->speed = speed;
	this->distance = distance;
}

AutoPilotState * AutoPilotState::_autoPilotState = NULL;

AutoPilotState::AutoPilotState(Experiment * e)
{
	// put us at the 'target' spot to begin with
	// FIXME
	//Controller::GetInstance()->getCamera()->getOrientation()->incrementPosition(new Vector3D(0,0,-100));

	int interval = Controller::GetInstance()->getTimer()->getInterval();

	HIGH_SPEED    = 14.66667/interval/1000.0;
	MID_SPEED     = 10.36667/interval/1000.0;
	//WALKING_SPEED = 
	LOW_SPEED     = 4.4/interval/1000.0;

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
	cout << "Enter AutoPilotState" << endl;

	static const int offset = 80;
	_currentTarget = new Vector3D(0, 0, -offset);

	Controller::GetInstance()->getCamera()->getOrientation()->setPosition(new Vector3D(0,0,0));
	Controller::GetInstance()->getCamera()->getOrientation()->addListener(this);

	//add the interpolation
	Controller::GetInstance()->getCamera()->getOrientation()->startMovingAlongFocalVector(.14667f);
			
			//	_trials[_experiment->getCurrentTrial()]->distance);
}

int AutoPilotState::handlePositionChange(Vector3D * position)
{
	if (_currentTarget->getZ() >= position->getZ()) {
		_experiment->setState(PreTrialState::GetInstance(_experiment));
	}

	//cout << _currentTarget->toString() << "\t" << position->toString() << endl;

	return 0;
}

void AutoPilotState::exitState()
{
	//remove the interpolation
	Controller::GetInstance()->getCamera()->getOrientation()->
		stopMovingAlongFocalVector();

	Controller::GetInstance()->getCamera()->getOrientation()->removeListener(this);

	Controller::GetInstance()->getCamera()->getOrientation()->setPosition(new Vector3D(0,0,0));
}

void AutoPilotState::generateSequence()
{
	SampleWithoutReplacement * swor = new SampleWithoutReplacement(
			0, _pairings.size() - 1, (int) (
				ceil((float)(_experiment->getNumberOfTrials()) / _pairings.size())
			));

	for (int i=0; i<_experiment->getNumberOfTrials(); i++) {
		_trials.push_back(_pairings[swor->sample()]);
	}
}

void AutoPilotState::handleRotationChange(float amount, const Vector3D * axis)
{
	// do nothing
}

