#ifndef KEYDOWNEVENT_H
#define KEYDOWNEVENT_H


#include "../../include/SDL.h"
#include "KeyEvent.h"


namespace XOR {

    /**
     * Represents a key being released. Contains information about the key that was released and modifier keys. Something to think about.
     * This really could just be an inner class of KeyEvent.
     */
class KeyDownEvent : public KeyEvent
{
    public:

        /**
         * Explicit constructor.
         */
        KeyDownEvent(SDL_keysym * keysym);


        /**
         * Returns "KEYDOWN" so you can tell what type of KeyEvent it is..
         */ 
        const int getType();


};

}

#endif          // KEYDOWNEVENT_H

