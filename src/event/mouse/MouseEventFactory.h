#ifndef MOUSEEVENTFACTORY_H
#define MOUSEEVENTFACTORY_H


#include <SDL/SDL.h>

#include <string>
#include "MouseEvent.h"
#include "MouseButtonDown.h"
#include "MouseButtonUp.h"
#include "MouseMotionEvent.h"


using namespace std;

namespace XOR {

/**
 * Convenience class for constructing mouse events. Can take raw SDL_Events of 
 * MOUSEMOTION or MOUSEBUTTON. Soon should contain explicit constructors for non-SDL
 * events.
 */
class MouseEventFactory
{
    public:

        /**
         * Factory constructor
         */
        static MouseEvent * ConstructInstance(SDL_Event * event);


		/**
		 * factory constructor
		 */
		static MouseEvent * ConstructInstance(string event);


        /**
         * construct an SDL event 
         */
        static SDL_Event * ConstructSDLEvent(string event);


    private:

        // no real need to create click factory, just a utility class
        MouseEventFactory();
 
        static SDL_Event _sdlMouseUpEvent;
        static SDL_Event _sdlMouseDownEvent;
        static SDL_Event _sdlMouseMoveEvent;
};

}

#endif          // MOUSEEVENTFACTORY_H
