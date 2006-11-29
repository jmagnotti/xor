#include "SpecialKeyEvent.h"

namespace XOR {

/*
 * explicit constructor
 */
SpecialKeyEvent::SpecialKeyEvent(int key)
{
	keyPressed = key;
	cursorX = 0;
	cursorY = 0;
	
}


/*
 * explicit constructor
 */
SpecialKeyEvent::SpecialKeyEvent(int key, int xpos, int ypos)
{
	keyPressed = key;
	cursorX = xpos;
	cursorY = ypos;
}


/*
 * get key pressed
 */
int SpecialKeyEvent::getKeyPressed()
{
	return keyPressed;
}

}

