#ifndef MULTICASTSOCKET_H
#define MULTICASTSOCKET_H


#include <string>
#include "multicast.h"


namespace XOR {

/**
 * Contains send() and receive() methods that use UDP broadcasting and
 * receiving. This class is not thread safe.
 */
class MulticastSocket
{

public:


    /**
     * Constructs a MulticastSocket and adds it to the given group on the given
     * port. This method does not perform OS specific initialization. If you
     * use the MulticastSocketPool, the initialization and group/port
     * specification will be handled for you.
     */
	MulticastSocket(const char * group, unsigned short port);

    
    /**
     * Broadcasts the messgae to the group. This function will block until the
     * message has been sent. Note that this is usually a negliglbe amount of
     * time, and need not be run in its own thread. Assumptions are no
     * substitute for testing on your local network though.
     */
    void send(string message);


    /**
     * Blocks until a message is picked up, or the socket is closed. This
     * function should typically be called in a thread separate from the main
     * renderingn thread, for timing reasons. Internally, event skeletons use
     * SDL_Threads, which work on most OSes (not OS9). See
     * xor/include/SDL_Thread.h for more
     * detail. 
     */
    string receive(void);


private:

    struct sockaddr_in _address;

    int _socket;

};


/**
 * takes care of the defaults for the keyboard socket
 */
class MulticastKeyboardSocket : public MulticastSocket
{

public:

    MulticastKeyboardSocket();

};


/**
 * takes care of the defaults for the Mouse socket
 */
class MulticastMouseSocket : public MulticastSocket
{

public:

   MulticastMouseSocket(); 

};


/**
 * Takes care of the defaults for the Timer socket
 */
class MulticastTimerSocket : public MulticastSocket
{

public:

    MulticastTimerSocket();

};


/*
 * user event channel
 */
class MulticastUserSocket: public MulticastSocket
{

public:

    MulticastUserSocket();

};


/*
 * error broadcaster, for those who want to listen to the complaints
 * of the framework.
 */
class MulticastErrorSocket : public MulticastSocket
{

public:

    MulticastErrorSocket();

};


}

#endif			// MULTICASTSOCKET_H

