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
	_currentX  = 0; _currentY = 0;
	_previousX = 0; _previousY = 0;

	_leftButtonDown = false; _middleButtonDown = false; _rightButtonDown = false;

    setCursorVisibility(_cursorVisible);
	_defaultMouseListener = NULL;
}

/*
 * set the default listener, return the old one or NULL on bad input or no
 * current listener
 */
MouseListener * Mouse::setDefaultMouseListener(MouseListener * defaultListener)
{
	MouseListener * returnVal = _defaultMouseListener;

	if (defaultListener != NULL)
		_defaultMouseListener = defaultListener;
	else
		returnVal = NULL;

	return returnVal;
}

/*
 * adds a listener
 */
void Mouse::addListener(MouseListener * listener)
{
	if (listener != NULL)
		_listeners.push_back(listener);
}

/*
 * fire a click event
 */
void Mouse::click(SDL_Event * event)
{
    fireEvent(MouseEventFactory::ConstructInstance(event));
}

/*
 * fire a move event
 */
void Mouse::move(SDL_Event * event)
{
    fireEvent(MouseEventFactory::ConstructInstance(event));
}

/*
 * Force move
 */
void Mouse::ForceMove(int xpos, int ypos)
{
    SDL_WarpMouse(xpos, ypos);
}

/*
 * Pushes the SDL event onto the main event queue
 */
void Mouse::FireSDLEvent(SDL_Event * event)
{
    SDL_PushEvent(event);
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
        if (button == MouseClickEvent::LEFT_MOUSE_BUTTON)
			_leftButtonDown = true;
		else if (button == MouseClickEvent::RIGHT_MOUSE_BUTTON)
			_rightButtonDown = true;
		else if (button == MouseClickEvent::MIDDLE_MOUSE_BUTTON)
			_middleButtonDown = true;
	}
	else {
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
	// let the default handler have the event first
	if (_defaultMouseListener != NULL)
		_defaultMouseListener->handleMouseEvent(me);

    list<MouseListener*>::iterator iter   = _listeners.begin();
    list<MouseListener*>::iterator next   = _listeners.begin();
    list<MouseListener*>::iterator finish = _listeners.end();

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

    list<MouseListener*>::iterator iter   = _listeners.begin();
    list<MouseListener*>::iterator finish = _listeners.end();

    while (!removed && iter != finish) {
        if (*iter == ml) {
            _listeners.erase(iter);
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

