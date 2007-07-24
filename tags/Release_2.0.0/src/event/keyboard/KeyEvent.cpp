#include "KeyEvent.h"


namespace XOR {

const int KeyEvent::KEY_DOWN_EVENT    = 0;
const int KeyEvent::KEY_UP_EVENT      = 1;

KeyEvent::KeyEvent()
{}

/*
 * Returns the SDLKey that was activated
 */
SDLKey KeyEvent::getKey()
{
    return _key;
}


/*
 * returns the modifer mask
 */
SDLMod KeyEvent::getModifiers()
{
    return _modifiers;
}


/*
 * returns the status of the shift key
 */
bool KeyEvent::isShiftPressed()
{
    return (KMOD_RSHIFT & _modifiers) || (KMOD_LSHIFT & _modifiers);
}


/*
 * returns the status of the alt key
 */
bool KeyEvent::isAltPressed()
{
    return  (KMOD_RALT & _modifiers) || (KMOD_LALT & _modifiers);
}


/*
 * returns the status of the meta key
 */
bool KeyEvent::isMetaPressed()
{
    return  (KMOD_RMETA & _modifiers) || (KMOD_LMETA & _modifiers);
}


/*
 * returns the status of the control key
 */
bool KeyEvent::isCtrlPressed()
{
    return  (KMOD_RCTRL & _modifiers) || (KMOD_LCTRL & _modifiers);
}

char * KeyEvent::toString()
{
	_eventString = new char[20];
	memset(_eventString, 0, sizeof(_eventString));
	sprintf(_eventString, "%d %d %d", getType(), getKey(), getModifiers());

    return _eventString;
}

}

