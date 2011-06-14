#include "SerialPortTimer.h"

SerialPortTimer * SerialPortTimer::_serialPortTimer= NULL;

void SerialPortTimer::handleTick()
{
    int status;

    //check the status of the DSR, notify listeners if state has changed
    ioctl(_fd, TIOCMGET, &status);


    if (_lastStatus != status) {
        _lastStatus = status;
        notifyListeners();
        //cout << "DSR: " << (TIOCM_DSR & status) << endl;
    }
}

void SerialPortTimer::removeListener(TimerListener * listener)
{
    bool removed = false;

    list<TimerListener*>::iterator iter   = _listeners.begin();
    list<TimerListener*>::iterator finish = _listeners.end();

    while (!removed && iter != finish) {
        if (*iter == listener) {
            _listeners.erase(iter);
            removed = true;
        }
        ++iter;
    }
}

void SerialPortTimer::notifyListeners()
{
    list<TimerListener*>::iterator iter   = _listeners.begin();
    list<TimerListener*>::iterator next   = _listeners.begin();
    list<TimerListener*>::iterator finish = _listeners.end();

    while (iter != finish) {
        ++next;
        (*iter)->handleTick();
        iter = next;
    }
}

void SerialPortTimer::addListener(TimerListener * listener)
{
	if (listener != NULL)
		_listeners.push_back(listener);
}

SerialPortTimer * SerialPortTimer::GetInstance()
{
    if (_serialPortTimer== NULL)
        _serialPortTimer= new SerialPortTimer();

    return _serialPortTimer;
}

SerialPortTimer::SerialPortTimer() {
  _fd = open("/dev/tty.PL2303-000014FA", O_RDWR | O_NOCTTY | O_NDELAY);
              //PL2303-000013FD

  if (_fd == -1) {
        //Could not open the port.  */
        cout << "Unable to open /dev/tty.PL2303-000014FA" << endl;
        cout << "Program is not likely to continue..." << endl;
  }
    else {
        cout << "Port open..." << endl;
    }

}

