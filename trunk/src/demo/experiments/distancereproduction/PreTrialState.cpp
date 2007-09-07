#include "PreTrialState.h"

PreTrialState * PreTrialState::_preTrialState = NULL;

PreTrialState::PreTrialState(Experiment * e)
{
	_experiment = e;
}

PreTrialState * PreTrialState::GetInstance(Experiment * e)
{
	if (_preTrialState == NULL)
		_preTrialState = new PreTrialState(e);	

	return _preTrialState;
}

void PreTrialState::handleKeyEvent(KeyEvent * ke)
{
	//detect 'start' key (space bar down event)
	if (KeyEvent::KEY_DOWN_EVENT == ke->getType() && 
		SDLK_SPACE == ke->getKey())
	{
		_experiment->setState(UserDrivenState::GetInstance(_experiment));
	}


}

void PreTrialState::handleMouseEvent(MouseEvent * me)
{
	// do nothing
}

void PreTrialState::enterState()
{
	cout << "Enter PreTrialState" << endl;
}

int PreTrialState::handlePositionChange(Vector3D * position)
{
}

void PreTrialState::exitState()
{
}

void PreTrialState::handleRotationChange(float amount, const Vector3D * axis)
{
	// do nothing
}

