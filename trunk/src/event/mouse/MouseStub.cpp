#include "MouseStub.h"


namespace XOR {

MouseStub * MouseStub::_mouseStub = 0;

/*
 * destructor
 */
MouseStub::~MouseStub()
{
	delete _socket;
}


/*
 * private constructor
 */
MouseStub::MouseStub()
{
	MulticastSocketPool * msp =	MulticastSocketPool::GetInstance();
	_socket = msp->getMulticastSocket(MulticastSocketPool::MOUSE_SOCKET);
}


/*
 * Singleton accessor
 */
MouseStub * MouseStub::GetInstance()
{
    if (_mouseStub == NULL)
        _mouseStub = new MouseStub();

    return _mouseStub;
}


/*
 * fire events to listeners
 */
void MouseStub::fireEvent(MouseEvent * me)
{
//	cout << "from stub: " << me->toString() << endl;

	_socket->send(me->toString());
    notifyListeners(me);
}

}

