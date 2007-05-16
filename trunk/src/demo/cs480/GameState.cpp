#include "GameState.h"

GameState::GameState()
{}


/*
 * Turn on/off timer listening
 */
void GameState::setTimerListen(bool listen)
{
	if (_timerListen != listen) {
		_timerListen = listen;

		if (_timerListen)
			Controller::GetInstance()->getTimer()->addListener(this);
		else
			Controller::GetInstance()->getTimer()->removeListener(this);
	}
}


/*
 * Turn on/off key listening
 */
void GameState::setKeyListen(bool listen)
{
	if (_keyListen != listen) {
		_keyListen = listen;

		if (_keyListen)
			Controller::GetInstance()->getKeyboard()->addListener(this);
		else
			Controller::GetInstance()->getKeyboard()->removeListener(this);
	}	
}


/*
 * Turn on/off mouse listening
 */
void GameState::setMouseListen(bool listen)
{
	if (_mouseListen != listen) {
		_mouseListen = listen;

		if (_mouseListen)
			Controller::GetInstance()->getMouse()->addListener(this);
		else
			Controller::GetInstance()->getMouse()->removeListener(this);
	}	
}

