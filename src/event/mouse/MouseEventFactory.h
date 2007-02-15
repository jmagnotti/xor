#ifndef MOUSEEVENTFACTORY_H
#define MOUSEEVENTFACTORY_H


#include "../../../include/SDL_events.h"

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
         * Returns the last event that was constructed by the factory. 
         * Here more for convenience than anything else.
        static MouseEvent * getLastEventConstructed();
         */


    private:

        // no real need to create click factory, just a utility class
        MouseEventFactory();
 
};

}

#endif          // MOUSEEVENTFACTORY_H
