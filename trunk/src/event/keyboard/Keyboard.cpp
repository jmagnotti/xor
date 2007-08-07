#include "Keyboard.h"

namespace XOR
{

const char * Keyboard::GROUP = "239.239.239.239";
const unsigned short Keyboard::PORT = 8393;

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

/*
 * add new listener
 */
void Keyboard::addListener(KeyboardListener* kl)
{
	_listeners.push_back(kl);
}

/*
 * sends a key event to all keyboard listeners
 */
void Keyboard::notifyListeners(KeyEvent * ke)
{
	// safe traversal in case anyone removes themselves contingent upon a key press
	list <KeyboardListener*>::iterator iter = _listeners.begin();
	list <KeyboardListener*>::iterator next = _listeners.begin();
	list <KeyboardListener*>::iterator finish = _listeners.end();

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
	fireKeyEvent(KeyEventFactory::ConstructInstance(&(event->key.type), &(event->key.keysym)));
}

/*
 * Push an event onto the SDL Event queue -- useful to call from other threads
 */
void Keyboard::FireSDLEvent(SDL_Event * event)
{
	SDL_PushEvent(event);
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

