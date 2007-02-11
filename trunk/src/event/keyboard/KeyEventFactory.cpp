#include "KeyEventFactory.h"


namespace XOR {

/*
 * Constructs the proper keyevent
 */
KeyEvent * KeyEventFactory::ConstructInstance(Uint8 * type, Uint8 * state, SDL_keysym * keysym)
{
    if ( *type == SDL_KEYDOWN || *state == SDL_PRESSED)
        return new KeyDownEvent(keysym);
    else
        return new KeyUpEvent(keysym);
}


/*
 * Returns an instance from the string
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
 * Default Constructor
 */
KeyEventFactory::KeyEventFactory()
{}


}

