#include "KeyFactory.h"


namespace XOR {

/*
 * Constructs the proper keyevent
 */
KeyEvent * KeyFactory::ConstructInstance(Uint8 * type, Uint8 * state, SDL_keysym * keysym)
{
    if ( *type == SDL_KEYDOWN || *state == SDL_PRESSED)
        return new KeyDownEvent(keysym);
    else
        return new KeyUpEvent(keysym);
}


/*
 * Default Constructor
 */
KeyFactory::KeyFactory()
{}


}

