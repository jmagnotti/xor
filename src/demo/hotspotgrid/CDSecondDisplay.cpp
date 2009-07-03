#include "CDSecondDisplay.h"

using namespace XOR;

CDSecondDisplay * CDSecondDisplay::_state = NULL;

CDSecondDisplay::CDSecondDisplay() 
{
}

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

	_grid->setVisibleLocations(s->getSecondLocations());
	_grid->setPictures(s->getSecondPictureIDs());
	_grid->setVisible(true);

	_grid->setMouseListen(true);
}


void CDSecondDisplay::handleChoice(int location)
{
	cout << "Choice Made:" << location << endl;
	_grid->setMouseListen(false);
	
	CDITIState * cdis = CDITIState::GetInstance(_grid);
	cdis->activate();
}

