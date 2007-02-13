#include "Mouse.h"

#include <iostream>
using namespace std;

namespace XOR {

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


void Mouse::click(SDL_Event * event)
{
    fireEvent(MouseEventFactory::ConstructInstance(event));
}


void Mouse::move(SDL_Event * event)
{
    fireEvent(MouseEventFactory::ConstructInstance(event));
}


/*
 * updates state variables from a motion event.
 */
void Mouse::updateFromEvent(MouseMotionEvent * mme)
{
    _previousX = _currentX;
    _previousY = _currentY;
    _currentX = mme->getXPosition();
    _currentY = mme->getYPosition();
}


/*
 * save state from a click event
 */
void Mouse::updateFromEvent(MouseClickEvent * mce)
{
    int button = mce->getButton();

	if (mce->getType() == MouseEvent::MOUSE_BUTTON_DOWN) {
        cout << "Mouse Down: " << button << endl;

        if (button == MouseClickEvent::LEFT_MOUSE_BUTTON)
			_leftButtonDown = true;
		else if (button == MouseClickEvent::RIGHT_MOUSE_BUTTON)
			_rightButtonDown = true;
		else if (button == MouseClickEvent::MIDDLE_MOUSE_BUTTON)
			_middleButtonDown = true;

	}
	else {
        cout << "Mouse Up: " << button << endl;

		if (button == MouseClickEvent::LEFT_MOUSE_BUTTON)
			_leftButtonDown = false;
		else if (button == MouseClickEvent::RIGHT_MOUSE_BUTTON)
			_rightButtonDown = false;
		else if (button == MouseClickEvent::MIDDLE_MOUSE_BUTTON)
			_middleButtonDown = false;

	}
}


/*
 * sends an event to listeners
 */
void Mouse::notifyListeners(MouseEvent * me)
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

