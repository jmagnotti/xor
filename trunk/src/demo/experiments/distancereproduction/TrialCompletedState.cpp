#include "TrialCompletedState.h"

TrialCompletedState * TrialCompletedState::_trialCompletedState = NULL;

TrialCompletedState::TrialCompletedState(Experiment * e)
{
	_string = new HidableRenderable(new Rectangle2D(
				new Vector2D(-.5, -.5),	
				new Vector2D(.5, .5),	
				new Paint(Color::YELLOW)
				));
	Controller::GetInstance()->getModel()->addObject("ITI", _string);
	_string->setVisible(false);
	_experiment = e;
}

TrialCompletedState * TrialCompletedState::GetInstance(Experiment * e)
{
	if (_trialCompletedState == NULL)
		_trialCompletedState = new TrialCompletedState(e);	

	return _trialCompletedState;
}

void TrialCompletedState::handleKeyEvent(KeyEvent * ke)
{
	// do nothing
}

void TrialCompletedState::handleMouseEvent(MouseEvent * me)
{
	// do nothing
}

void TrialCompletedState::enterState()
{
	cout << "Enter TrialCompletedState" << endl;
	_string->setVisible(true);

	IntervalTimer::GetInstance()->addListener(this, 3000, false);
}

void TrialCompletedState::handleTick()
{
	_experiment->setState(AutoPilotState::GetInstance(_experiment));
}

void TrialCompletedState::handleRotationChange(float amount, const Vector3D * axis)
{
	// do nothing
}

int TrialCompletedState::handlePositionChange(Vector3D * position)
{
	// do nothing
}

void TrialCompletedState::exitState()
{
	_string->setVisible(false);
}
