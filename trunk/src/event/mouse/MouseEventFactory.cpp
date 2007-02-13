#include "MouseEventFactory.h"


namespace XOR {


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


/*
 * no real need to create click factory, just a utility class
 */
MouseEventFactory::MouseEventFactory()
{}

}

