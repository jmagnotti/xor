#include "LoseState.h"

LoseState * LoseState::_state = NULL;

/*
 * Returns the current instance
 */
LoseState * LoseState::getInstance()
{
    if (_state == NULL)
        _state = new LoseState();

    return _state;	
}

/*
 * Destructor
 */
LoseState::~LoseState()
{
    delete _state;
}

LoseState::LoseState()
{
}

/*
 * Handles user key events using the XOR framework
 */
void LoseState::handleKey(KeyEvent * ke)
{
    //does nothing yet
}

/*
 * Handles user key events using the XOR framework
 */
void LoseState::handleKeyEvent(KeyEvent * ke)
{
    //do nothing
}


/*
 * Handles timer tick events using the XOR framework
 */
void LoseState::handleTick()
{
    //does nothing yet
}


/*
 * Handles mouse motion and mouse click events using
 * the XOR framework
 */
void LoseState::handleMouseEvent(MouseEvent * me)
{
    //does nothing yet
}


/*
 * This method turns collision detection off, sets
 * the key and mouse listeners to ON
 */
void LoseState::in()
{
    setTimerListen(false);
    setMouseListen(false);
    setKeyListen(true);
}


/*
 * Clean up before exit
 */
void LoseState::out()
{
    setTimerListen(false);
    setMouseListen(false);
    setKeyListen(true);
}

