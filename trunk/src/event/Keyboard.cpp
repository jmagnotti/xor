#include "Keyboard.h"


namespace XOR {


/*
 * add new listener
 */
void Keyboard::addListener(KeyboardListener* kl)
{
	listeners.push_back(kl);
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
 * turns 
 */ 
void Keyboard::generateKeyEvent(SDL_Event * event)
{
   regularKeyEvent(event->key.which, 0, 0);
}


/*
 * remove existing listener
 */
void Keyboard::removeListener(KeyboardListener* kl)
{
	bool found = false;
	vector <KeyboardListener*>::iterator iter = listeners.begin();

	while (iter != listeners.end() && !found) {
		if (*iter == kl) {		
			listeners.erase(iter);
			found = true;
		}
		++iter;
	}
}


/*
 * regular event notification
 */
void Keyboard::regularKeyEvent(Uint8 key)
{
	RegularKeyEvent *rke = new RegularKeyEvent(key, x, y);

	vector <KeyboardListener*>::iterator iter = listeners.begin();

	while (iter != listeners.end()) {
		(*iter)->handleKey(rke);
		++iter;
	}
	
	delete rke;
}

}

