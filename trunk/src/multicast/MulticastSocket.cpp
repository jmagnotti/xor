#include "MulticastSocket.h"


namespace XOR {

/*
 * 
 */
MulticastSocket::MulticastSocket(const char * group, unsigned short port)
{
    int success;

    /* create a socket for sending to the multicast _address */
    _socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    /* set the TTL (time to live/hop count) for the send */
    success = setsockopt(_socket, IPPROTO_IP, IP_MULTICAST_TTL, (opt_type)
            &mc_ttl, sizeof(mc_ttl))

    /* construct a multicast address structure */
    memset(&_address, 0, sizeof(_address));
    _address.sin_family      = AF_INET;
    _address.sin_addr.s_addr = inet_addr(address_str);
    _address.sin_port        = htons(mc_port);

    if (success < 0 || _socket < 0) {
        //set failure condition
    }

}


/*
 * broadcast a message
 */
void MulticastSocket::send(string message)
{
    int length = sendto(_socket, message.c_str(), strlen(message.c_str()),
            0, (struct sockaddr *) &_address, sizeof(_address));

    if (length < message.size() ) {
        // error condition
    }

}



string MulticastSocket::receive()
{
    string message;
    int length;

    length = recvfrom(sock, recv_str, MAX_LEN, 0, (struct sockaddr*)&from_addr,
            (socklen_t *) &from_len);

    if (length < 0) {
       // error condition
    }

    return message;

}

}

