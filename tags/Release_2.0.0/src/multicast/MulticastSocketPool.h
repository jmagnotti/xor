#ifndef MULTICASTSOCKETPOOL_H
#define MULTICASTSOCKETPOOL_H 

#include <list>

#include "Multicast.h"
#include "MulticastSocket.h"

using namespace std;

namespace XOR
{

/**
 * Factory and container for MulticastSockets. Provides constants for selecting
 * the appropriate socket type, and takes care of initializing and closing
 * OS-specific socket interfaces. This class does not handle the actual closing
 * of the socket.
 */
class MulticastSocketPool
{

public:

    /**
     * Socket constants. These are used so classes can participate in the
     * appropriate communication channel. These constants are initialized in
     * the header file so they may be used in switch statements. See Paint.h
     * for further discussion of this.
     */
    static const int ERROR_SOCKET = -1;
    static const int KEYBOARD_SOCKET = 0;
    static const int TIMER_SOCKET = 1;
    static const int MOUSE_SOCKET = 2;
    static const int USER_EVENT_SOCKET = 9;

    /**
     * Singleton Accessor.
     */
    static MulticastSocketPool * GetInstance();

    /**
     * Returns a pointer to a multicast socket. See MulticastSocket.h for usage
     * notes. On Windows, the Pool takes care of starting the socket API and
     * closing it. The actual creation and later closing of sockets is done by
     * the MulticastSocket object.
     */
    MulticastSocket * getMulticastSocket(const int type);

    /**
     * Closes all the sockets in the pool. Because the pool contains framework
     * sockets, this should only be called by the Controller upon program
     * termination.
     */
    void cleanUpAndExit();

private:

    MulticastSocketPool();

    static MulticastSocketPool * _multicastSocketPool;
    list<MulticastSocket*> _sockets;

};

}

#endif          // MULTICASTSOCKETPOOL_H
