#include <sys/types.h>   /* for type definitions */
#include <sys/socket.h>  /* for socket API function calls */
#include <netinet/in.h>  /* for address structs */
#include <arpa/inet.h>   /* for sockaddr_in */
#include <stdio.h>       /* for printf() */
#include <stdlib.h>      /* for atoi() */
#include <string.h>      /* for strlen() */
#include <unistd.h>      /* for close() */

#define MAX_LEN  1024    /* maximum string size to send */
#define MIN_PORT 1024    /* minimum port allowed */
#define MAX_PORT 65535   /* maximum port allowed */

int mcsend(char *addr, unsigned short port, char *msg) {

  int sock;                   /* socket descriptor */
  char send_str[MAX_LEN];     /* string to send */
  struct sockaddr_in mc_addr; /* socket address structure */
  unsigned int send_len;      /* length of string to send */
  char* mc_addr_str;          /* multicast IP address */
  unsigned short mc_port;     /* multicast port */
  unsigned char mc_ttl=1;     /* time to live (hop count) */

  mc_addr_str = "239.239.239.239";       /* arg 1: multicast IP address */
  mc_port     = 1234;		 /* arg 2: multicast port number */
  msg = "Hello world\n";
 
 /* create a socket for sending to the multicast address */
  if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
    perror("socket() failed");
    exit(1);
  }
  
  /* set the TTL (time to live/hop count) for the send */
  if ((setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, 
       (void*) &mc_ttl, sizeof(mc_ttl))) < 0) {
    perror("setsockopt() failed");
    exit(1);
  } 
  
  /* construct a multicast address structure */
  memset(&mc_addr, 0, sizeof(mc_addr));
  mc_addr.sin_family      = AF_INET;
  mc_addr.sin_addr.s_addr = inet_addr(mc_addr_str);
  mc_addr.sin_port        = htons(mc_port);

    /* send string to multicast address */
    if ((sendto(sock, msg, strlen(msg), 0, 
         (struct sockaddr *) &mc_addr, 
         sizeof(mc_addr))) != strlen(msg)) {
      printf("sendto() sent incorrect number of bytes");
      exit(1);
    }
  
  close(sock);  

  exit(0);
}


