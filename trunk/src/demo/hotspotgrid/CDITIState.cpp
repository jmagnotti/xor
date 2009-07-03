#include "CDITIState.h"

using namespace XOR;

CDITIState * CDITIState::_state = NULL;

CDITIState::CDITIState() {
}

CDITIState * CDITIState::GetInstance(CDGrid * grid) {
	if (NULL == _state)
		_state = new CDITIState();

	_state->_grid = grid;

	return _state;
}

void CDITIState::activate()
{
	_grid->setVisible(false);

	IntervalTimer::GetInstance()->addListener(this, 2000, false);

	bool next = Session::GetInstance()->nextTrial();
	if (!next)
		Controller::GetInstance()->CleanUpAndExit();
}


void CDITIState::handleTick()
{
	CDFixateState * cdfs = CDFixateState::GetInstance(_grid);
	cdfs->activate();
}

