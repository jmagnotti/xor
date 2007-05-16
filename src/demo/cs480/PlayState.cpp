#include "PlayState.h"

PlayState * PlayState::_state = NULL;

/*
 * Returns the current instance
 */
PlayState * PlayState::GetInstance(Game * game)
{
	if (_state == NULL)
		_state = new PlayState(); 
	_state->_game = game; 
	return _state;	
}

PlayState::PlayState()
{}

/*
 * Destructor
 */
PlayState::~PlayState()
{
	delete _state;
}

/**
 * Handles user key events using the XOR framework
 */
void PlayState::handleKeyEvent(KeyEvent * ke)
{}


/*
 * Handles timer tick events using the XOR framework
 */
void PlayState::handleTick()
{
	//display time, or use separate sprite?
}


/*
 * Handles mouse motion and mouse click events using
 * the XOR framework
 */
void PlayState::handleMouseEvent(MouseEvent * me)
{
	//does nothing yet
}


/**
 * This method turns collision detection off, sets
 * the key and mouse listeners to ON
 */
void PlayState::in()
{
	int xmid = Controller::GetInstance()->getWindow()->getSize()->getWidth() / 2.0;
	// this gens an event, might be bad
	//SDL_WarpMouse(xmid,0);
	SDL_ShowCursor(false);

	_game->_ball->setMovementVector(new Vector3D(.1,0,.5));

	_game->_ball->addListener(_game->_bricks);
	_game->_ball->addListener(_game->_paddle);
	_game->_ball->addListener(_game->_gameSpace);

	_game->_ball->begin();
	_game->_paddle->begin();

	Controller::GetInstance()->getKeyboard()->addListener(_game->_paddle);

	setKeyListen(true);	
}


/**
 * Clean up before exit
 */
void PlayState::out()
{
	_game->getBall()->end();
	//setMouseListen(false);	
	Controller::GetInstance()->getKeyboard()->removeListener(_game->getPaddle());
	setKeyListen(false);	
	setTimerListen(false);	
}

