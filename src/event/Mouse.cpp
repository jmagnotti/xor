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

}

