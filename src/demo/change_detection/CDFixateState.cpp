#include "CDFixateState.h"

using namespace XOR;

CDFixateState * CDFixateState::_state = NULL;

CDFixateState::CDFixateState() {
	//this is a vector to avoid overloading method in CDGrid
	_fixationLocation.push_back(0);
	_fixationImageFile.push_back(string(""));
}

CDFixateState * CDFixateState::GetInstance(CDGrid * grid) {
	if (NULL == _state)
		_state = new CDFixateState();

	_state->_grid = grid;

	return _state;
}

void CDFixateState::activate()
{
	Session * s = Session::GetInstance();

	//this is a vector to avoid overloading method in CDGrid
	_fixationImageFile[0] = s->getFixationFile();

	_grid->setVisibleLocations(_fixationLocation);
	_grid->setImageFiles(_fixationImageFile);
	_grid->setVisible(true);

	IntervalTimer::GetInstance()->addListener(this, s->getFixationDuration(), false);

}

void CDFixateState::handleTick()
{
	CDInitialDisplay * cdid = CDInitialDisplay::GetInstance(_grid);
	cdid->activate();
}

