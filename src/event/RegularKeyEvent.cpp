#include "RegularKeyEvent.h"

namespace XOR {

/*
 * explicit constructor
 */
RegularKeyEvent::RegularKeyEvent(unsigned char key)
{
	keyPressed = key;
	cursorX = 0;
	cursorY = 0;
}


/*
 * explicit constructor
 */
RegularKeyEvent::RegularKeyEvent(unsigned char key, int xpos, int ypos)
{
	keyPressed = key;
	cursorX = xpos;
	cursorY = ypos;
}


/*
 * get key pressed
 */
unsigned char RegularKeyEvent::getKeyPressed()
{
	return keyPressed;
}

}

