#include "AutoPilotState.h"

AutoPilotState * AutoPilotState::_autoPilotState = NULL;

AutoPilotState::AutoPilotState(Experiment * e)
{
	HIGH_SPEED    = 14.66667;
	MID_SPEED    = 14.66667;
	LOW_SPEED    = 14.66667;

	LONG_DISTANCE = 100;
	SHORT_DISTANCE = 60;

	_experiment = e;
	_trialNumber = 0;

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
	vector<int> poss_distances;
	vector<int> poss_speeds;
	poss_distances.push_back(60);
	poss_distances.push_back(100);

	poss_speeds.push_back(4.);
	poss_speeds.push_back();
	poss_speeds.push_back();

	// calculate a random sequence of translations for the camera
	SampleWithoutReplacement * rnd_d  = SampleWithoutReplacement(poss_distances, 42);
	SampleWithoutReplacement * rnd_s = SampleWithoutReplacement(poss_speeds, 27);
	
}
