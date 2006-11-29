#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H


namespace XOR {

/**
 * Parent class for mouse events
 */
class MouseEvent
{

public:


	/**
	 * Default Constructor
	 */
	MouseEvent();


	//-- GETTERS --//
	int getType();

	int getXPosition();
	int getYPosition();

protected:

	int _xpos, _ypos;
	int _type;


};

}

#endif          //MOUSEEVENT_H

