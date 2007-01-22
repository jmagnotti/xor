#include "RemoteEventHandlerFactory.h"

namespace XOR {

// set the singleton to 0 
RemoteEventHandlerFactory * RemoteEventHandlerFactory::_remoteEventHandlerFactory = 0;

/*
 * Accessor
 */
RemoteEventHandlerFactory * RemoteEventHandlerFactory::GetInstance()
{
    if (_remoteEventHandlerFactory == 0)
        _remoteEventHandlerFactory = new RemoteEventHandlerFactory();

    return _remoteEventHandlerFactory;
}


/*
 * returns a remote keyboard
 */
Keyboard * RemoteEventHandlerFactory::getKeyboard()
{
    return KeyboardStub::GetInstance();
}


/*
 * returns a remote timer
 */
Timer * RemoteEventHandlerFactory::getTimer()
{
    return TimerStub::GetInstance();
}


/*
 * returns a remote mouse
 */
Mouse * RemoteEventHandlerFactory::getMouse()
{
    return MouseStub::GetInstance();
}

/*
 * returns a local reshape
 */
Reshape * RemoteEventHandlerFactory::getReshape()
{
    return ReshapeSkeleton::GetInstance();
}

/*
 * private constructor
 */
RemoteEventHandlerFactory::RemoteEventHandlerFactory()
{}

}

