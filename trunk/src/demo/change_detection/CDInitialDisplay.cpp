#include "CDInitialDisplay.h"

using namespace XOR;

CDInitialDisplay * CDInitialDisplay::_state = NULL;

CDInitialDisplay::CDInitialDisplay()
{ }

CDInitialDisplay * CDInitialDisplay::GetInstance(CDGrid * grid) {
	if (NULL == _state)
		_state = new CDInitialDisplay();

	_state->_grid = grid;

	return _state;
}

void CDInitialDisplay::activate()
{
	Session * s = Session::GetInstance();

	_grid->setVisibleLocations(s->getSampleStimulusLocations());
	_grid->setImageFiles(s->getSampleStimulusFiles());
	_grid->setVisible(true);

	IntervalTimer::GetInstance()->addListener(this, s->getSampleDisplayDuration(), false);
}

void CDInitialDisplay::handleTick()
{
	CDRetentionInterval * cdri = CDRetentionInterval::GetInstance(_grid);
	cdri->activate();
}

