#ifndef MOUSESTUB_H
#define MOUSESTUB_H


#include "MouseEvent.h"
#include "Mouse.h"


using namespace std;

namespace XOR {

/**
 * 
 */
class MouseStub : public Mouse
{

public:

	/**
	 * Fires an event to listeners
	 */
	void fireEvent(MouseEvent * me);


	/**
	 * Singleton Constructor
	 */
	static MouseStub * GetInstance(void);


private:

    MouseStub();

	static MouseStub * _mouseStub;

};

}

#endif			// MOUSESTUB_H

