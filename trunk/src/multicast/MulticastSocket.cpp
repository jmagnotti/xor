#include "MulticastSocket.h"


namespace XOR {

const short  MulticastSocket::MAX_LENGTH = 1024;

const char * MulticastSocket::MULTICAST_GROUP = "239.239.239.239";	


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
    cout << "Building multicast socket with " << group << ":" << port << endl;

    int success;
	int on = 1;

	_joined = false;
	_bound = false;

	/* create a socket for sending to the multicast address */
    _socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	/* set the TTL (time to live/hop count) for the send */
	success = setsockopt(_socket, IPPROTO_IP, IP_MULTICAST_TTL, (opt_type) &on,
			sizeof(on));

	/* construct a multicast address structure */
    memset(&_multicastAddress, 0, sizeof(_multicastAddress));
    _multicastAddress.sin_family      = AF_INET;
    _multicastAddress.sin_addr.s_addr = inet_addr(group);
    _multicastAddress.sin_port        = htons(port);

	/* construct an IGMP join request structure */
	_request.imr_multiaddr.s_addr = inet_addr(group);
	_request.imr_interface.s_addr = INADDR_ANY;


    if (success < 0 || _socket < 0) {
        //set failure condition
    }

    perror("From constructor");
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

    cout << message.size() << endl;

    int length = sendto(_socket, message.c_str(), message.size() + 1, 0, (struct sockaddr *) &_multicastAddress, sizeof(_multicastAddress));

    /* if (length < message.size() ) { cout << "only " << length << " bytes sent" << endl; } */

    cout << "Sent " << length << " bytes" << endl;

    perror("From Send");
}


/*
 * receive from the group, then return the input as a string
 */
string MulticastSocket::receive()
{
	char buffer[MAX_LENGTH+1];
    int length;
    string message;


    if (! _bound)
        bind(_socket, (struct sockaddr *) &_multicastAddress, sizeof(_multicastAddress));


	/* clear the receive buffers & structs */
	memset(buffer, 0, MAX_LENGTH+1);

    unsigned int sz =sizeof(_remoteAddress);

	memset(&_remoteAddress, 0, sz);

	length = recvfrom(_socket, buffer, MAX_LENGTH, 0, (struct sockaddr*)
			&_remoteAddress, (socklen_t *) sz);

    cout << "Receive " <<  length << " bytes" << endl;
    perror("From Receive");

    /* if (length < message.size() ) { cout << "only " << length << " bytes received" << endl; } */

	message = string(buffer);

    return message;
}


MulticastMouseSocket::MulticastMouseSocket() :
	MulticastSocket(MULTICAST_GROUP, 1234)
{}

MulticastKeyboardSocket::MulticastKeyboardSocket() :
	MulticastSocket(MULTICAST_GROUP, 1235)
{}

MulticastUserSocket::MulticastUserSocket() :
	MulticastSocket(MULTICAST_GROUP, 1236)
{}


MulticastTimerSocket::MulticastTimerSocket() :
	MulticastSocket(MULTICAST_GROUP, 1237)
{}

MulticastErrorSocket::MulticastErrorSocket() :
	MulticastSocket(MULTICAST_GROUP, 1238)
{}

}

