#include "CDSecondDisplay.h"

using namespace XOR;

CDSecondDisplay * CDSecondDisplay::_state = NULL;

CDSecondDisplay::CDSecondDisplay() 
{ }

CDSecondDisplay * CDSecondDisplay::GetInstance()
{
	if (NULL == _state)
		_state = new CDSecondDisplay();

	return _state;
}

CDSecondDisplay * CDSecondDisplay::GetInstance(CDGrid * grid)
{
	if (NULL == _state)
		_state = new CDSecondDisplay();

	_state->_grid = grid;

	return _state;
}

void CDSecondDisplay::activate()
{
	Session * s = Session::GetInstance();

	_grid->setMouseListen(true);

	_grid->setVisibleLocations(s->getChoiceStimulusLocations());
	_grid->setImageFiles(s->getChoiceStimulusFiles());
	_grid->setVisible(true);

	_reactionTime = Controller::GetInstance()->getTimer()->getElapsedTime(); 
}


void CDSecondDisplay::handleChoice(int location)
{
	_reactionTime = Controller::GetInstance()->getTimer()->getElapsedTime() - _reactionTime;
	_grid->setMouseListen(false);

	Session::GetInstance()->recordChoice(location, _reactionTime);
	
	CDITIState * cdis = CDITIState::GetInstance(_grid);
	cdis->activate();
}

