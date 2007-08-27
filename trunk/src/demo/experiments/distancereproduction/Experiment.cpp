#include "Experiment.h"

Experiment::Experiment()
{}

~Experiment::Experiment()
{
	_state->exitState();
	delete _state;
}

void Experiment::handleKeyEvent(KeyEvent * ke)
{
	_state->handleKeyEvent(ke);
}

void Experiment::handleMouseEvent(MouseEvent * me)
{
	_state->handleMouseEvent(me);
}

void ExperimentalState::setState(ExperimentalState * state)
{
	if (_state != NULL)
		_state->exitState();

	_state = state;
	_state->enterState();	
}

