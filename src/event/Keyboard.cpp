#include "Keyboard.h"


namespace XOR {

// set the static instance to 0
Keyboard * Keyboard::_keyboard = 0;


/*
 * add new listener
 */
void Keyboard::addListener(KeyboardListener* kl)
{
	_listeners.push_back(kl);
}


/*
 * Singleton accessor
 */
Keyboard * Keyboard::GetInstance()
{
    if (_keyboard == NULL)
        _keyboard = new Keyboard();

    return _keyboard;
}


/*
 * sends a key event to all keyboard listeners
 */
void Keyboard::fireKeyEvent(KeyEvent * ke) 
{
    // safe traversal in case anyone removes themselves contingent upon a key press
	list <KeyboardListener*>::iterator iter     = _listeners.begin();
	list <KeyboardListener*>::iterator next     = _listeners.begin();
	list <KeyboardListener*>::iterator finish   = _listeners.end();

    while (iter != finish) {
        ++next;
		(*iter)->handleKeyEvent(ke);
        iter = next;
	}
}


/*
 * Turns SDL Events into something that the Keyboard can fire off to listeners
 */ 
void Keyboard::generateKeyEvent(SDL_Event * event)
{
    fireKeyEvent(KeyFactory::ConstructInstance(&(event->key.type), &(event->key.state), &(event->key.keysym))) ;
}


/*
 * remove existing listener
 */
void Keyboard::removeListener(KeyboardListener* kl)
{
	bool found = false;
	list <KeyboardListener*>::iterator iter = _listeners.begin();

	while (iter != _listeners.end() && !found) {
		if (*iter == kl) {		
			_listeners.erase(iter);
			found = true;
		}
		++iter;
	}
}


}

