#include "Window.h"


namespace XOR {

const char * Window::DEFAULT_WINDOW_TITLE	= "Project Xavier | 2.0 alpha";

const int Window::DEFAULT_WINDOW_X		= 200;
const int Window::DEFAULT_WINDOW_Y		= 100;

const int Window::DEFAULT_WINDOW_WIDTH	= 900;
const int Window::DEFAULT_WINDOW_HEIGHT	= 825;


SDL_Event Window::_reshape = { SDL_VIDEORESIZE };

/**
 * constructs the window
 */
void Window::build(Vector2D * origin, Dimension2D * size, char * title)
{
    _origin = origin;
    _size   = size;

    setTitle(title);
}

   
/**
 * Default constructor.
 *
 * Builds a window according to the preset defaults.
 */
Window::Window()
{
    build(new Vector2D(DEFAULT_WINDOW_X, DEFAULT_WINDOW_Y), 
          new Dimension2D(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT),
          (char *) DEFAULT_WINDOW_TITLE);
}


/*
 * exp cstr
 */
Window::Window(Vector2D * origin, Dimension2D * size, char * title)
{
    build(origin, size, title);
}


/**
 * Returns a constant reference to the dimension of this window.
 */
Dimension2D * Window::getSize() const
{
    return _size;
}


/**
 * Generates a reshape event from the SDL_Event
 */
void Window::generateEvent(SDL_Event * event)
{
    // catch potentially dangerous resizes
    if (event->resize.w <= 0 || event->resize.h <= 0) {
        event->resize.w = (int) _size->getWidth();
        event->resize.h = (int) _size->getHeight();
    }
        
    notifyListeners(ReshapeEvent::ConstructInstance(
                new Dimension2D(event->resize.w, event->resize.h)));

    setTitle(_title);
}


/**
 * Notifies listeners of the reshape event
 */
void Window::notifyListeners(ReshapeEvent * event)
{
    list<ReshapeListener*>::iterator iter   = _listeners.begin();
	list<ReshapeListener*>::iterator next   = _listeners.begin();
    list<ReshapeListener*>::iterator finish = _listeners.end();

    while (iter != finish) {
		++next;
		(*iter)->handleReshape(event);
        iter = next;
    }
}


/*
 * Adds a listener
 */
void Window::addListener(ReshapeListener * rl)
{
    _listeners.push_back(rl);
}


/*
 * Remove a listener from the pool. Should be re-written to use "find" instead
 * of iterating ourselves.
 */
void Window::removeListener(ReshapeListener * rl)
{
    bool removed = false;

    list<ReshapeListener*>::iterator iter   = _listeners.begin();
    list<ReshapeListener*>::iterator finish = _listeners.end();

    while (!removed && iter != finish) {
        if (*iter == rl) {
            _listeners.erase(iter);
            removed = true;
		}
		else {
			++iter;
		}
    }
}


/**
 * Sets the title of the window
 */
void Window::setTitle(char * title) 
{
    _title = title;
    SDL_WM_SetCaption(_title, "Xavier");
}

void Window::ForceReshape()
{
    _reshape.resize.w = -1;
    _reshape.resize.h = -1;
    SDL_PushEvent(&_reshape);
}

}

