#ifndef MCSEND_H
#define MCSEND_H

#include "multicast.h"

namespace XOR {

class MCSend
{

public:
	MCSend(const char *mc_addr_str, unsigned short mc_port);
	void send(char *msg);

private:
	int sock; /* socket descriptor */
	struct sockaddr_in mc_addr; /* socket address structure */
};

}

#endif //MCSEND_H
