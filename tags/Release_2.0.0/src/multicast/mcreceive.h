#ifndef MCRECEIVE_H
#define MCRECEIVE_H

#include "Multicast.h"

namespace XOR {

class MCReceive
{

public:
	MCReceive(const char *mc_addr_str, unsigned short mc_port);
	void send(char *msg);

private:
	int sock; /* socket descriptor */
	struct sockaddr_in mc_addr; /* socket address structure */
};

}

#endif			//MCRECEIVE_H
