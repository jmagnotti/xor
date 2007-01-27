#ifndef MULTICASTSOCKET_H
#define MULTICASTSOCKET_H


#include "multicast.h"


namespace XOR {

/**
 * Encapsulates sending and receiving of UDP Broadcasts.
 */
class MulticastSocket
{

public:

	MulticastSocket();

private:


};




/**
 * takes care of the defaults for the keyboard socket
 */
class MulticastKeyboardSocket : MulticastSocket
{

public:

    MulticastKeyboardSocket();

};

/**
 * takes care of the defaults for the Mouse socket
 */
class MulticastMouseSocket 
{

public:

   MulticastMouseSocket(); 

};


/**
 * Takes care of the defaults for the Timer socket
 */
class MulticastTimerSocket 
{

public:

    MulticastTimerSocket();

};


}

#endif			// MULTICASTSOCKET_H

