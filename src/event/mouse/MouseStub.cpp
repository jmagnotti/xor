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
    if (me->getType() == MouseEvent::MOUSE_MOTION)
        updateFromEvent((MouseMotionEvent*)me);
    else 
        updateFromEvent((MouseClickEvent *)me);

	_socket->send(me->toString());
    notifyListeners(me);
}

}

