#include "KeyUpEvent.h"


namespace XOR {

/*
 * Explicit constructor
 */
KeyUpEvent::KeyUpEvent(SDL_keysym * keysym)
{
    _modifiers  = &(keysym->mod);
    _key        = &(keysym->sym);
}


/*
 *
 */
const int KeyUpEvent::getType()
{
    return KeyEvent::KEY_UP_EVENT;
}

}


