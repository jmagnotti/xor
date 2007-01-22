#ifndef REGKEYEVENT_H
#define REGKEYEVENT_H


namespace XOR {

/**
 * RegularKeyEvent.h
 * Definition of a regular(ASCII VALUE) key event
 */
class RegularKeyEvent
{

protected:
	unsigned char	keyPressed;
			 int	cursorX, cursorY;

public:

	/**
	 * Default constructor
	 */
	RegularKeyEvent(unsigned char key);


	/**
	 * Constructor for Regular key event
	 * unsigned char: the ascii key presed
	 * int: the 
	 */
	RegularKeyEvent(unsigned char key, int xpos, int ypos);


	/**
	 * Returns the key pressed
	 */
	unsigned char getKeyPressed();

};

}

#endif			//REGKEYEVENT_H

