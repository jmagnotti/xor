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

	if (s->getReportingMethod() == Session::METHOD_CHANGE_NOCHANGE) {
		Controller::GetInstance()->getMouse()->addListener(this);
	}
	else {
		_grid->setMouseListen(true);
	}

	_grid->setVisibleLocations(s->getChoiceStimulusLocations());
	_grid->setImageFiles(s->getChoiceStimulusFiles());


	_grid->setVisible(true);

	_reactionTime = Controller::GetInstance()->getTimer()->getElapsedTime(); 
}

void CDSecondDisplay::handleMouseEvent(MouseEvent * me)
{
	if (me->getType() == MouseEvent::MOUSE_BUTTON_DOWN) {
		if (Controller::GetInstance()->getMouse()->isLeftButtonDown()) {
			handleChoice(1);
			cout << "Chose Same" << endl;
		}
		else {
			handleChoice(-1);
			cout << "Chose Different" << endl;
		}

	}
}

void CDSecondDisplay::handleChoice(int location)
{
	_reactionTime = Controller::GetInstance()->getTimer()->getElapsedTime() - _reactionTime;
	_grid->setMouseListen(false);

	Session * s = Session::GetInstance();
	s->recordChoice(location, _reactionTime);

	if (s->getReportingMethod() == Session::METHOD_CHANGE_NOCHANGE) {
		Controller::GetInstance()->getMouse()->removeListener(this);
	}
	else {
		_grid->setMouseListen(false);
	}
	
	CDITIState * cdis = CDITIState::GetInstance(_grid);
	cdis->activate();
}

