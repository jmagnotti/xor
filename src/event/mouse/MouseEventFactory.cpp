#include "MouseEventFactory.h"

#include <iostream>
using namespace std;

namespace XOR {

SDL_Event MouseEventFactory::_sdlMouseUpEvent   = {SDL_MOUSEBUTTONUP};
SDL_Event MouseEventFactory::_sdlMouseDownEvent = {SDL_MOUSEBUTTONDOWN};
SDL_Event MouseEventFactory::_sdlMouseMoveEvent = {SDL_MOUSEMOTION};

/*
 * Factory constructor.
 */
MouseEvent * MouseEventFactory::ConstructInstance(SDL_Event * event)
{
	MouseEvent * mouseEvent;

    if (event->type == SDL_MOUSEMOTION)
        mouseEvent =  new MouseMotionEvent(event->motion.x, event->motion.y,
                                    event->motion.xrel, event->motion.yrel);

    else if (event->type == SDL_MOUSEBUTTONDOWN)
        mouseEvent =  new MouseButtonDown(event->button.x, event->button.y,
                                          event->button.button);
    else 
        mouseEvent =  new MouseButtonUp(event->button.x, event->button.y,
                                        event->button.button);

    return mouseEvent;
}


/*
 * 
 */
MouseEvent * MouseEventFactory::ConstructInstance(string event)
{
    //#FIXME
	MouseEvent * mouseEvent;

	char * result = NULL;
	char delims[] = " ";

	result = strtok((char *)event.c_str(), delims);
	int type   = atoi(result);

	int xpos   = atoi(strtok(NULL, delims));
	int ypos   = atoi(strtok(NULL, delims));
	int param3 = atoi(strtok(NULL, delims));

	if (type == MouseEvent::MOUSE_MOTION) {
		int param4 = atoi(strtok(NULL, delims));
		mouseEvent =  new MouseMotionEvent(xpos, ypos, param3, param4);
	}
    else if (type == MouseEvent::MOUSE_BUTTON_UP) {
		mouseEvent =  new MouseButtonUp(xpos, ypos, param3);
	}
    else {
        mouseEvent =  new MouseButtonDown(xpos, ypos, param3);
	}

	return mouseEvent;
}


SDL_Event * MouseEventFactory::ConstructSDLEvent(string event)
{
	//cout << "Attempting to build a mouse event from: " << event << endl;
	char * result = NULL;
	char delims[] = " ";

	result = strtok((char *)event.c_str(), delims);
	int type   = atoi(result);

	int xpos   = atoi(strtok(NULL, delims));
	int ypos   = atoi(strtok(NULL, delims));
	int param3 = atoi(strtok(NULL, delims));

	if (type == MouseEvent::MOUSE_MOTION) {
		//cout << "Mouse Motion" << endl;
		int param4 = atoi(strtok(NULL, delims));
        _sdlMouseMoveEvent.motion.x = xpos;
        _sdlMouseMoveEvent.motion.y = ypos;
        _sdlMouseMoveEvent.motion.xrel = param3;
        _sdlMouseMoveEvent.motion.yrel = param4;

        return & _sdlMouseMoveEvent;
	}
    else if (type == MouseEvent::MOUSE_BUTTON_UP) {
		//cout << "Mouse Up" << endl;
        _sdlMouseUpEvent.button.x = xpos;
        _sdlMouseUpEvent.button.y = ypos;
        _sdlMouseUpEvent.button.button = param3;

        return & _sdlMouseUpEvent;
	}
    else {
		//cout << "Mouse Down" << endl;
        _sdlMouseDownEvent.button.x = xpos;
        _sdlMouseDownEvent.button.y = ypos;
        _sdlMouseDownEvent.button.button = param3;

        return & _sdlMouseDownEvent;
    }

}


/*
 * no real need to create click factory, just a utility class
 */
MouseEventFactory::MouseEventFactory()
{}

}

