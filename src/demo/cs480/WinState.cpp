#include "WinState.h"

WinState * WinState::_state = NULL;

/*
 * Returns the current instance
 */
WinState * WinState::GetInstance(Game * game)
{
	if (_state == NULL)
		_state = new WinState();

	_state->_game = game;

	return _state;	
}

/*
 * Destructor
 */
WinState::~WinState()
{
	delete _state;
}

WinState::WinState()
{}

/*
 * Handles user key events using the XOR framework
 */
void WinState::handleKey(KeyEvent * ke)
{

}

/**
 * Handles user key events using the XOR framework
 */
void WinState::handleKeyEvent(KeyEvent * ke)
{

}


/*
 * Handles timer tick events using the XOR framework
 */
void WinState::handleTick()
{}


/*
 * Handles mouse motion and mouse click events using
 * the XOR framework
 */
void WinState::handleMouseEvent(MouseEvent * me)
{
	//does nothing yet
}


/**
 * This method turns collision detection off, sets
 * the key and mouse listeners to ON
 */
void WinState::in()
{
	setMouseListen(true);
	setKeyListen(true);
}


/**
 * Clean up before exit
 */
void WinState::out()
{
	setMouseListen(false);
	setKeyListen(false);
}
