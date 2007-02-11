#ifndef MOUSESTUB_H
#define MOUSESTUB_H


#include "MouseEvent.h"
#include "Mouse.h"
#include "../../multicast/MulticastSocketPool.h"
#include "../../multicast/MulticastSocket.h"

using namespace std;

namespace XOR {

/**
 * 
 */
class MouseStub : public Mouse
{

public:


	/**
	 * Destructor
	 */
    virtual ~MouseStub();

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

	MulticastSocket  * _socket;

};

}

#endif			// MOUSESTUB_H

