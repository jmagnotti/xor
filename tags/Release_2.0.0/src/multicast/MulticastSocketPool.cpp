#include "MulticastSocketPool.h"


namespace XOR {

 MulticastSocketPool * MulticastSocketPool::_multicastSocketPool = NULL;

MulticastSocketPool::MulticastSocketPool()
{

#ifdef WIN32
    WORD wVersionRequested;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD(2, 0);

    if(WSAStartup(wVersionRequested, &wsaData) != 0) {
        // error condition
    }

#endif

}

MulticastSocketPool * MulticastSocketPool::GetInstance()
{
	if (_multicastSocketPool == NULL)
		_multicastSocketPool = new MulticastSocketPool();

	return _multicastSocketPool;
}


MulticastSocket * MulticastSocketPool::getMulticastSocket(const int type)
{
	switch(type) {
		case ERROR_SOCKET :
			return new MulticastErrorSocket();
			break;
		case TIMER_SOCKET :
			return new MulticastTimerSocket();
			break;
		case MOUSE_SOCKET :
			return new MulticastMouseSocket();
			break;
		case KEYBOARD_SOCKET :
			return new MulticastKeyboardSocket();
			break;
		default :
			return new MulticastUserSocket();
			break;
	}
}


/*
 * close the sockets and close API specific settings
 */
void MulticastSocketPool::cleanUpAndExit()
{
    list<MulticastSocket*>::iterator iter   = _sockets.begin();
    list<MulticastSocket*>::iterator next   = _sockets.begin();
    list<MulticastSocket*>::iterator finish = _sockets.end();

    while(iter != finish) {
        ++next;
        delete (*iter);
        iter = next;
    }

#ifdef WIN32
	WSACleanup();
#endif

}

}

