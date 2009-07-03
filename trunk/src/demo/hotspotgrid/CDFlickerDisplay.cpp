#include "CDFlickerDisplay.h"

using namespace XOR;

CDFlickerDisplay * CDFlickerDisplay::_state = NULL;

CDFlickerDisplay::CDFlickerDisplay() {
}

CDFlickerDisplay * CDFlickerDisplay::GetInstance(CDGrid * grid) {
	if (NULL == _state)
		_state = new CDFlickerDisplay();

	_state->_grid = grid;

	return _state;
}

void CDFlickerDisplay::activate()
{
	_grid->setVisible(false);

	int delay = Session::GetInstance()->getProbeDelay();

	if (delay > 0) {
		IntervalTimer::GetInstance()->addListener(this, delay , false);
	}
	else {
		//NO flicker condition
		CDSecondDisplay * cdsd = CDSecondDisplay::GetInstance(_grid);
		cdsd->activate();
	}
}


void CDFlickerDisplay::handleTick()
{
	//cout << "Handing to CDSecond from Flicker" << endl;
	CDSecondDisplay * cdsd = CDSecondDisplay::GetInstance(_grid);
	cdsd->activate();
}

