#ifndef KEYEVENT_H
#define KEYEVENT_H


#include "../../include/SDL.h"


namespace XOR {

/**
 * I want to keep this as generic as possible for now.
 * The idea for now is that the constructor will return either KeyUpEvent or KeyDownEvent 
 * objects. Later we could save (even preload!) KeyEvents that we know are going to be used.
 * This would speed things up as we aren't creating and deleting objects all over the place. 
 * We can't reflect on the KeyboardListener to find out which methods it has implemented, but 
 * there should be another way to find out what keys they are using and create a bunch of them.
 * A fun side effect is that we can ignore keypresses that the listeners don't care about.
 */
class KeyEvent 
{

    public:

        // constants for the two types of key events
        static const int KEY_DOWN_EVENT;
        static const int KEY_UP_EVENT;
        // --

        /**
         * Returns the key that was either pressed or released
         */
        SDLKey * getKey();


        /**
         * Returns the modifier mask
         */
        SDLMod * getModifiers();


        bool isShiftPressed();


        bool isAltPressed();


        bool isMetaPressed();


        bool isCtrlPressed();


        /**
         * Returns the type of event, either "KEYUP" or "KEYDOWN"
         */
        virtual const int getType()=0;


    protected:
    
        KeyEvent()
        {}

        SDLKey  *   _key;
        SDLMod  *   _modifiers;
};

}

#endif          // KEYEVENT_H

