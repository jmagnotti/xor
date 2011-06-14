#ifndef SERIAL_PORT_TIMER_H
#define SERIAL_PORT_TIMER_H

#include "../../xor.h"


#include <stdlib.h>
#include <list>
#include <SDL/SDL.h>

#include <stdio.h>   /* Standard input/output definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include "sys/ioctl.h"
#include <unistd.h>

using namespace XOR;
using namespace std;


class SerialPortTimer : public TimerListener
{
public:

	virtual ~SerialPortTimer (){}

    static SerialPortTimer * GetInstance();


	//timer handle
	void handleTick(); 

    void removeListener(TimerListener * listener);

    void addListener(TimerListener * listener);

    //this really should be private, but see CDDriver for access need
    void notifyListeners();

private:


    SerialPortTimer();

    static SerialPortTimer * _serialPortTimer;


	list <TimerListener*>  _listeners;

    int _fd, _lastStatus;
};

#endif			// CDSTATE_H

