#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include "sys/ioctl.h"
#include <unistd.h>

#include "iostream"

using namespace std;

/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */

int
open_port(void)
{
  int fd; /* File descriptor for the port */


  fd = open("/dev/tty.PL2303-000014FA", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
       /*
        * Could not open the port.
        */
        perror("open_port: Unable to open /dev/ttyS0 - ");
  }
  else
        
    fcntl(fd, F_SETFL, 0);

  return (fd);
}

int main (int argc, char **argv) {

    int status, fd;
    /*
     * Get the current options for the port...
     */

    fd = open_port();
    ioctl(fd, TIOCMGET, &status);

    cout << "DSR: " << (TIOCM_DSR & status) << endl;


    return 0;
}

