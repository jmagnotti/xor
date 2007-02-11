#ifndef KEYEVENTFACTORY_H
#define KEYEVENTFACTORY_H


#include <stdlib.h>
#include <string>
#include "../../../include/SDL.h"

#include "KeyEvent.h"
#include "KeyDownEvent.h"
#include "KeyUpEvent.h"


namespace XOR {

/**
 * Factory for key presses. I want to keep this as generic as possible for now.
 * The idea for now is that the constructor will return either KeyUpEvent or KeyDownEvent 
 * objects. Later we could save (even preload!) KeyEvents that we know are going to be used.
 * This would speed things up as we aren't creating and deleting objects all over the place. 
 * We can't reflect on the KeyboardListener to find out which methods it has implemented, but 
 * there should be another way to find out what keys they are using and create a bunch of them.
 * A fun side effect is that we can ignore keypresses that the listeners don't care about.
 */
class KeyEventFactory
{
    public:

        /**
         * Factory constructor
         * Using both type & state, although they are basically the same thing. Should decide if this matters.
         */
		static KeyEvent * ConstructInstance(Uint8 * type, Uint8 * state, SDL_keysym * keysym);

		static KeyEvent * ConstructInstance(string event);

    private:

        KeyEventFactory();

};

}

#endif          // KEYEVENTFACTORY_H

