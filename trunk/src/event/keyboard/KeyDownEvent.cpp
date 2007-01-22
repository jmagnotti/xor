#include "KeyDownEvent.h"


namespace XOR {

/*
 * Explicit constructor
 */
KeyDownEvent::KeyDownEvent(SDL_keysym * keysym)
{
    _modifiers  = keysym->mod;
    _key        = keysym->sym;
}


/*
 *
 */
const int KeyDownEvent::getType()
{
    return KeyEvent::KEY_DOWN_EVENT;
}


}

