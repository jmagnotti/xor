#include "Mouse.h"

namespace XOR {

//initialize static instance to NULL
Mouse * Mouse::_mouse = 0;


/* 
 * private constructor
 */
Mouse::Mouse()
{

    _cursorVisible = false;
    setCursorVisibility(_cursorVisible);
    
	_leftDown			    	= 0;
	_currentX	= _currentY 	= 0;
	_startX		= _startY	    = 0;
	_previousX	= _previousY    = 0;
}


/*
 * adds a listener
 */
void Mouse::addListener(MouseListener * ml)
{
    listeners.push_back(ml);
}


/*
 * Handles click events
 */
void Mouse::click(int button, int state, int x, int y)
{
	if (false)
           // button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		_leftDown = 1;

		_currentX = x;
		_currentY = y;

		_startX = x;
		_startY = y;
	}
	else if (false)
            //_leftDown == 1 && button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		_leftDown = 0;

		_currentX = x;
		_currentY = y;

		_startX = x;
		_startY = y;
	}

	fireEvent(new MouseClickEvent(button, state, x, y));
}


/*
 * sends an event to listeners
 */
void Mouse::fireEvent(MouseEvent * me)
{

    vector<MouseListener*>::iterator iter   = listeners.begin();
    vector<MouseListener*>::iterator finish = listeners.end();

	if (me->getType() == 2) {
        while (iter != finish) {
			(*iter)->handleMouseEvent((MouseClickEvent*)me);
			++iter;
		}
	}
	else {
		while (iter != finish) {
			(*iter)->handleMouseEvent((MouseMotionEvent*)me);
			++iter;
		}
	}

}


/*
 * singleton accessor
 */
Mouse* Mouse::GetInstance(void)
{
	if (_mouse == NULL)
		_mouse = new Mouse();

	return _mouse;
}


/*
 * singleton accessor with explicit add
 */
Mouse * Mouse::GetInstance(MouseListener* ml)
{
	if (_mouse == NULL)
		_mouse = new Mouse();

	_mouse->addListener(ml);

	return _mouse;
}


/*
 * Handles mouse movements
 */
void Mouse::motion(int x, int y)
{
	_previousX = _currentX;
	_previousY = _currentY;

	if (_leftDown == 1) 
	{
		_currentX = x;
		_currentY = y;
	} 
	else			//simulates mouse drag
	{
		_currentX = x;
		_currentY = y;

		_startX = x;
		_startY = y;
	}


	fireEvent(new MouseMotionEvent(x, y));
}


/*
 * Removes the mouselistener from the pool
 */
void Mouse::removeListener(MouseListener * ml)
{
    bool removed = false;

    vector<MouseListener*>::iterator iter   = listeners.begin();
    vector<MouseListener*>::iterator finish = listeners.end();

    while (iter != finish && !removed) {
        if (*iter == ml) {
            listeners.erase(iter);
            removed = true;
        }
        ++iter;
    }
}

void Mouse::setCursorVisibility(bool show)
{
    if (_cursorVisible != show) {
        _cursorVisible = show;
        SDL_ShowCursor(_cursorVisible);
    }
}

//---GETTERS---//
int	Mouse::getLeftDown()	{ return _leftDown;	}
int	Mouse::getStartX()		{ return _startX;	}
int	Mouse::getStartY()		{ return _startY;	}
int	Mouse::getPreviousX()	{ return _previousX;}
int	Mouse::getPreviousY()	{ return _previousY;}
int Mouse::getCurrentX()	{ return _currentX;	}
int Mouse::getCurrentY()	{ return _currentY;	}

}

