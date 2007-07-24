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
 * exp cstr
 */
KeyDownEvent::KeyDownEvent(int key, int mods)
{
	_key = (SDLKey)key;
	_modifiers = (SDLMod)mods;
}


/*
 *
 */
const int KeyDownEvent::getType()
{
    return KeyEvent::KEY_DOWN_EVENT;
}

}

