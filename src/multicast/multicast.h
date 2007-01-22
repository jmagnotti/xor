#ifndef MULTICAST_H
#define MULTICAST_H

#include <sys/types.h>   /* for type definitions */
#include <stdio.h>       /* for printf() */
#include <stdlib.h>      /* for atoi() */
#include <string.h>      /* for strlen() */
#ifdef WIN32
#include <winsock2.h>         // For socket(), connect(), send(), and recv()
#include <ws2tcpip.h>
//namespace XOR {
typedef int socklen_t;
typedef const char* opt_type;       // Type used for raw data on this platform
//}
#else
#include <sys/socket.h>  /* for socket API function calls */
#include <netinet/in.h>  /* for address structs */
#include <arpa/inet.h>   /* for sockaddr_in */
#include <unistd.h>      /* for close() */
//namespace XOR {
typedef void* opt_type;
//}
#endif

#endif			// MULTICAST_H
