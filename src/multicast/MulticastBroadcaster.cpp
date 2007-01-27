#include "MulticastBroadcaster.h"


namespace XOR {

MulticastBroadcaster::MulticastBroadcaster()
{
	Controller * ctrl = Controller::GetInstance();
	ctrl->getKeyboard()->addListener(this);
	mcsend = new MCSend("239.239.239.239", 1234);
}

void MulticastBroadcaster::handleKeyEvent(KeyEvent * ke)
{
	if(ke->getKey() != 300) {
		char * buffer = new char[20];
		sprintf(buffer, "%d %d\n", ke->getKey(), ke->getModifiers());

		printf("PRINT: %s", buffer);

		mcsend->send(buffer);
	}
}

}
