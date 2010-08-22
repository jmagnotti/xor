#include "CDInitialDisplay.h"

using namespace XOR;

CDInitialDisplay * CDInitialDisplay::_state = NULL;

CDInitialDisplay::CDInitialDisplay() {
}

CDInitialDisplay * CDInitialDisplay::GetInstance(CDGrid * grid) {
	if (NULL == _state)
		_state = new CDInitialDisplay();

	_state->_grid = grid;

	return _state;
}

void CDInitialDisplay::activate()
{
	Session * s = Session::GetInstance();

	_grid->setVisibleLocations(s->getInitialLocations());
	_grid->setPictures(s->getInitialPictureIDs());

	//s->getSampleDisplayDuration();
	IntervalTimer::GetInstance()->addListener(this, 1000, false);

	_grid->setVisible(true);
}


void CDInitialDisplay::handleTick()
{
	CDRetentionInterval * cdri = CDRetentionInterval::GetInstance(_grid);
	cdri->activate();
}

