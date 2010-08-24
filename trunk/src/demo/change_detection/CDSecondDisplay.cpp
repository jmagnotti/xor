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
	//this looks dirty, but makes the input so clean [not sure why]
	Mouse::ForceMove(640,512);

	Session * s = Session::GetInstance();

	_grid->setMouseListen(true);

	_grid->setVisibleLocations(s->getChoiceStimulusLocations());
	_grid->setImageFiles(s->getChoiceStimulusFiles());
	_grid->setVisible(true);

}


void CDSecondDisplay::handleChoice(int location)
{
	// recording choice
	cout << "Choice Made:" << location << endl;
	
	_grid->setMouseListen(false);
	
	CDITIState * cdis = CDITIState::GetInstance(_grid);
	cdis->activate();
}

