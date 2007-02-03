#include "MulticastSocket.h"


namespace XOR {

	
/*
 * Private default constructor
 */
MulticastSocket::MulticastSocket()
{}


/*
 * destructor, closes socket
 */
MulticastSocket::~MulticastSocket()
{
	if (_joined) {
		setsockopt(_socket, IPPROTO_IP, IP_DROP_MEMBERSHIP, (opt_type)
				&_request, sizeof(_request));
	}

#ifdef WIN32
	closesocket(_socket);
#else
	close(_socket);
#endif

}

/*
 * 
 */
MulticastSocket::MulticastSocket(const char * group, unsigned short port)
{
    int success;
	int on = 1;

	_joined = false;

	/* create a socket for sending to the multicast address */
    _socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	/* set the TTL (time to live/hop count) for the send */
	success = setsockopt(_socket, IPPROTO_IP, IP_MULTICAST_TTL, (opt_type) &on,
			sizeof(on));

	/* construct a multicast address structure */
    memset(&_localAddress, 0, sizeof(_localAddress));
    _localAddress.sin_family      = AF_INET;
    _localAddress.sin_addr.s_addr = inet_addr(group);
    _localAddress.sin_port        = htons(port);

	/* construct an IGMP join request structure */
	_request.imr_multiaddr.s_addr = inet_addr(group);
	_request.imr_interface.s_addr = INADDR_ANY;

	bind(_socket, (struct sockaddr *) &_localAddress, sizeof(_localAddress));

    if (success < 0 || _socket < 0) {
        //set failure condition
    }

}


/*
 * broadcast a message
 */
void MulticastSocket::send(string message)
{
	if (! _joined) {
		setsockopt(_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (opt_type)&_request,
				sizeof(_request));
		_joined = true;
	}

    int length = sendto(_socket, message.c_str(), strlen(message.c_str()),
            0, (struct sockaddr *) &_remoteAddress, sizeof(_remoteAddress));

    if (length < message.size() ) {
        // error condition
    }

}


/*
 * receive from the group, then return the input as a string
 */
string MulticastSocket::receive()
{
	char buffer[MAX_LENGTH+1];     /* buffer to receive string */
    string message;
    unsigned int length;

	/* clear the receive buffers & structs */
	memset(buffer, 0, MAX_LENGTH+1);
	memset(&_remoteAddress, 0, sizeof(_remoteAddress));

	length = recvfrom(_socket, buffer, MAX_LENGTH, 0, (struct sockaddr*)
			&_remoteAddress, (socklen_t *) sizeof(_remoteAddress));

    if (length < 0) {
       // error condition
    }

	message = string(buffer);

    return message;
}


MulticastMouseSocket::MulticastMouseSocket() :
	MulticastSocket("239.239.239.239", 1234)
{}

MulticastKeyboardSocket::MulticastKeyboardSocket() :
	MulticastSocket("239.239.239.239", 1235)
{}

MulticastUserSocket::MulticastUserSocket() :
	MulticastSocket("239.239.239.239", 1236)
{}


MulticastTimerSocket::MulticastTimerSocket() :
	MulticastSocket("239.239.239.239", 1237)
{}

MulticastErrorSocket::MulticastErrorSocket() :
	MulticastSocket("239.239.239.239", 1238)
{}

}

