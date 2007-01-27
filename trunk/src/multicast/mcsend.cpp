#include "mcsend.h"


namespace XOR {


int main(int argc, char* argv[])
{
	MCSend* mcsend = new MCSend("239.239.239.239", 1234);
	mcsend->send("hello world");
}


/**
 *
 */

/**
 *
 */
MCSend::MCSend(const char *mc_addr_str, unsigned short mc_port)
{
	unsigned char mc_ttl=1;

	#ifdef WIN32
        WORD wVersionRequested;
        WSADATA wsaData;

        wVersionRequested = MAKEWORD(2, 0);

        if(WSAStartup(wVersionRequested, &wsaData) != 0)
            perror("Unable to load WinSock DLL");

	#endif

	/* create a socket for sending to the multicast address */
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		perror("socket() failed");

	/* set the TTL (time to live/hop count) for the send */
    if ((setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (opt_type) &mc_ttl,
                    sizeof(mc_ttl))) < 0) { perror("setsockopt() failed");
	}

	/* construct a multicast address structure */
	memset(&mc_addr, 0, sizeof(mc_addr));
	mc_addr.sin_family      = AF_INET;
	mc_addr.sin_addr.s_addr = inet_addr(mc_addr_str);
	mc_addr.sin_port        = htons(mc_port);
}

void MCSend::send(char *msg)
{
	/* send string to multicast address */
    if ((sendto(sock, msg, strlen(msg), 0, (struct sockaddr *) &mc_addr,
                    sizeof(mc_addr))) != strlen(msg)) {
		perror("sendto() sent incorrect number of bytes");
	}
}

}

/**Deconstructor
	#ifdef WIN32
	closesocket(sock);
	WSACleanup();
	#else
	close(sock);
	#endif
*/
