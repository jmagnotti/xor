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
	_currentX = 0;
	_currentY = 0;
	_previousX = 0;
	_previousY = 0;
	_leftButtonDown = false;
	_rightButtonDown = false;
	_middleButtonDown = false;
    setCursorVisibility(_cursorVisible);
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
void Mouse::click(SDL_Event * event)
{
    fireEvent(MouseEventFactory::ConstructInstance(event));
}


/*
 * sends an event to listeners
 */
void Mouse::fireEvent(MouseEvent * me)
{
	int button;

	// update local variables
	if (me->getType() == MouseEvent::MOUSE_MOTION)
	{
		_previousX = _currentX;
		_previousY = _currentY;
		_currentX = me->getXPosition();
		_currentY = me->getYPosition();
	}
	else if (me->getType() == MouseEvent::MOUSE_BUTTON_DOWN)
	{
		button = ((MouseClickEvent*)me)->getButton();
		if (button == MouseClickEvent::LEFT_MOUSE_BUTTON)
		{
			_leftButtonDown = true;
		}
		else if (button == MouseClickEvent::RIGHT_MOUSE_BUTTON)
		{
			_rightButtonDown = true;
		}
		else if (button == MouseClickEvent::MIDDLE_MOUSE_BUTTON)
		{
			_middleButtonDown = true;
		}
	}
	else // if (me->getType() == MouseEvent::MOUSE_BUTTON_UP)
	{
		button = ((MouseClickEvent*)me)->getButton();
		if (button == MouseClickEvent::LEFT_MOUSE_BUTTON)
		{
			_leftButtonDown = false;
		}
		else if (button == MouseClickEvent::RIGHT_MOUSE_BUTTON)
		{
			_rightButtonDown = false;
		}
		else if (button == MouseClickEvent::MIDDLE_MOUSE_BUTTON)
		{
			_middleButtonDown = false;
		}
	}

    list<MouseListener*>::iterator iter   = listeners.begin();
    list<MouseListener*>::iterator next   = listeners.begin();
    list<MouseListener*>::iterator finish = listeners.end();

    while (iter != finish) {
        ++next;
        (*iter)->handleMouseEvent(me);
        iter = next;
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
void Mouse::move(SDL_Event * event)
{
	fireEvent(MouseEventFactory::ConstructInstance(event));
}


/*
 * Removes the mouselistener from the pool
 */
void Mouse::removeListener(MouseListener * ml)
{
    bool removed = false;

    list<MouseListener*>::iterator iter   = listeners.begin();
    list<MouseListener*>::iterator finish = listeners.end();

    while (iter != finish && !removed) {
        if (*iter == ml) {
            listeners.erase(iter);
            removed = true;
        }
        ++iter;
    }
}


/*
 * sets the visibility of the cursor
 */
void Mouse::setCursorVisibility(bool show)
{
    if (_cursorVisible != show) {
        _cursorVisible = show;
        SDL_ShowCursor(_cursorVisible);
    }
}


/*
 * current X accessor
 */
int Mouse::getCurrentX()
{
	return _currentX;
}


/*
 * current Y accessor
 */
int Mouse::getCurrentY()
{
	return _currentY;
}


/*
 * previous X accessor
 */
int Mouse::getPreviousX()
{
	return _previousX;
}


/*
 * previous Y accessor
 */
int Mouse::getPreviousY()
{
	return _previousY;
}


/*
 * left button status accessor
 */
bool Mouse::isLeftButtonDown()
{
	return _leftButtonDown;
}


/*
 * right button status accessor
 */
bool Mouse::isRightButtonDown()
{
	return _rightButtonDown;
}


/*
 * middle button status accessor
 */
bool Mouse::isMiddleButtonDown()
{
	return _middleButtonDown;
}


}

