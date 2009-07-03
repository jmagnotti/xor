#include "CDFixateState.h"

using namespace XOR;

CDFixateState * CDFixateState::_state = NULL;

CDFixateState::CDFixateState() {
	_positions.push_back(0);
}

CDFixateState * CDFixateState::GetInstance(CDGrid * grid) {
	if (NULL == _state)
		_state = new CDFixateState();

	_state->_grid = grid;

	return _state;
}

void CDFixateState::activate()
{
	_grid->showFixation();

	IntervalTimer::GetInstance()->addListener(this, 500, false);
}


void CDFixateState::handleTick()
{
	CDInitialDisplay * cdid = CDInitialDisplay::GetInstance(_grid);
	cdid->activate();
}

