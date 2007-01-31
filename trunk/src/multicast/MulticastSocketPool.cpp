#include "MulticastSocketPool.h"


namespace XOR {

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


/*
 * close the sockets and close API specific settings
 */
MulticastSocketPool::CleanUpAndExit()
{
    list<MulticastSocket*>::iterator iter   = _sockets.begin();
    list<MulticastSocket*>::iterator next   = _sockets.begin();
    list<MulticastSocket*>::iterator finish = _sockets.end();

    while(iter != finish) {
        ++next;
        (*iter)->close();
        iter = next;
    }

#ifdef WIN32
	WSACleanup();
#endif

}


}

