#include "KeyUpEvent.h"


namespace XOR {

/*
 * Explicit constructor
 */
KeyUpEvent::KeyUpEvent(SDL_keysym * keysym)
{
    _modifiers  = keysym->mod;
    _key        = keysym->sym;
}

/*
 * exp cstr
 */
KeyUpEvent::KeyUpEvent(int key, int mods)
{
	_key = (SDLKey)key;
	_modifiers = (SDLMod)mods;
}


/*
 *
 */
const int KeyUpEvent::getType()
{
    return KeyEvent::KEY_UP_EVENT;
}

}


