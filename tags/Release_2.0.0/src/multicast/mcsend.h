#ifndef MCSEND_H
#define MCSEND_H

#include "Multicast.h"

namespace XOR {

class MCSend
{

public:

    /**
     * Construct a multicast socket with the given group and port.
     */
	MCSend(const char *mc_addr_str, unsigned short mc_port);


    /*
     * broadcast a message
     */
	void send(char *msg);

private:

	int sock; /* socket descriptor */

	struct sockaddr_in mc_addr; /* socket address structure */

};

}

#endif          // MCSEND_H

