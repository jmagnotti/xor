#include "MouseSkeleton.h"
#include <iostream>


namespace XOR {

MouseSkeleton * MouseSkeleton::_mouseSkeleton = NULL;
MulticastSocket * MouseSkeleton::_socket = NULL;

bool MouseSkeleton::_keepGoing = true;

/*
 * private constructor
 */
MouseSkeleton::MouseSkeleton()
{
	_socket = MulticastSocketPool::GetInstance()->getMulticastSocket(
			  MulticastSocketPool::MOUSE_SOCKET);

	_thread = SDL_CreateThread(& MouseSkeleton::Listen, NULL);
}


/*
 * destructor
 */
MouseSkeleton::~MouseSkeleton()
{
	_keepGoing = false;
	delete _socket;
}


/*
 * Fires an event to listeners
 */
void MouseSkeleton::fireEvent(MouseEvent * me)
{
    //cout << "Firing event" << endl;
    if (me->getType() == MouseEvent::MOUSE_MOTION)
        updateFromEvent((MouseMotionEvent*)me);
    else 
        updateFromEvent((MouseClickEvent *)me);

    notifyListeners(me);
}


/*
 * Singleton Constructor
 */
MouseSkeleton * MouseSkeleton::GetInstance()
{
    if (_mouseSkeleton == NULL)
        _mouseSkeleton = new MouseSkeleton();

    return _mouseSkeleton;
}

int MouseSkeleton::Listen(void * data)
{
	string msg; 

	while(_keepGoing) {
		msg = _socket->receive();	
        Mouse::FireSDLEvent(MouseEventFactory::ConstructSDLEvent(msg));
	}

    return 0;
}

}

