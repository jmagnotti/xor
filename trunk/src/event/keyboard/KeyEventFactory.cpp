#include "KeyEventFactory.h"

#include <iostream>
using namespace std;

namespace XOR {

/**
 * Set the 'inner type' of the SDL_Events
 */
SDL_Event KeyEventFactory::_sdlKeyDownEvent = {SDL_KEYDOWN};
SDL_Event KeyEventFactory::_sdlKeyUpEvent   = {SDL_KEYUP};

/*
 * Constructs the proper keyevent
 */
KeyEvent * KeyEventFactory::ConstructInstance(Uint8 * type, SDL_keysym * keysym)
{
    if (*type == SDL_KEYDOWN)
        return new KeyDownEvent(keysym);
    else
        return new KeyUpEvent(keysym);
}


/*
 * Returns an instance from the string
 * #TODO needs error handling
 */
KeyEvent * KeyEventFactory::ConstructInstance(string event)
{
	char * result = NULL;
	char delims[] = " ";

	result = strtok((char *)event.c_str(), delims);
	int type = atoi(result);

	result = strtok(NULL, delims);
	int key = atoi(result); 
	
	result = strtok(NULL, delims);
	int mod = atoi(result);

	if (type == SDL_KEYDOWN)
		return new KeyDownEvent(key, mod);
	else
		return new KeyUpEvent(key, mod);
}


/*
 * Returns an instance from the string.
 * #TODO needs error handling
 */
SDL_Event * KeyEventFactory::ConstructSDLEvent(string event)
{
	//cout << "Trying to create keyboard event from : " << event << endl;
	char * result = NULL;
	char delims[] = " ";

	result = strtok((char *)event.c_str(), delims);
	int type = atoi(result);

	result = strtok(NULL, delims);
	int key = atoi(result); 
	
	result = strtok(NULL, delims);
	int mod = atoi(result);

	if (type == SDL_KEYDOWN) {
		//cout << "\tKeyDown" << endl;
        _sdlKeyDownEvent.key.keysym.sym = (SDLKey)key;
        _sdlKeyDownEvent.key.keysym.mod = (SDLMod)mod;

        return & _sdlKeyDownEvent;
    }
    else {
		//cout << "\tKeyUp" << endl;
        _sdlKeyUpEvent.key.keysym.sym = (SDLKey)key;
        _sdlKeyUpEvent.key.keysym.mod = (SDLMod)mod;

        return & _sdlKeyUpEvent;
    }

}

}

