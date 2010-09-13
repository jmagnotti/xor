#include "CDRetentionInterval.h"

using namespace XOR;

CDRetentionInterval * CDRetentionInterval::_state = NULL;

CDRetentionInterval::CDRetentionInterval() {
}

CDRetentionInterval * CDRetentionInterval::GetInstance(CDGrid * grid) {
	if (NULL == _state)
		_state = new CDRetentionInterval();

	_state->_grid = grid;

	return _state;
}

void CDRetentionInterval::activate()
{
	_grid->setVisible(false);

	int retention = Session::GetInstance()->getRetentionInterval();

	if (retention > 0) {
		IntervalTimer::GetInstance()->addListener(this, retention, false);
	}
	else {
		//No-delay condition
		CDSecondDisplay * cdsd = CDSecondDisplay::GetInstance(_grid);
		cdsd->activate();
	}
}

void CDRetentionInterval::handleTick()
{
	CDSecondDisplay * cdsd = CDSecondDisplay::GetInstance(_grid);
	cdsd->activate();
}

