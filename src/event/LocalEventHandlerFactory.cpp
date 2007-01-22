#include "LocalEventHandlerFactory.h"

namespace XOR {

// set the singleton to 0 
LocalEventHandlerFactory * LocalEventHandlerFactory::_localEventHandlerFactory = 0;

/*
 * Accessor
 */
LocalEventHandlerFactory * LocalEventHandlerFactory::GetInstance()
{
    if (_localEventHandlerFactory == 0)
        _localEventHandlerFactory = new LocalEventHandlerFactory();

    return _localEventHandlerFactory;
}


/*
 * returns a local keyboard
 */
Keyboard * LocalEventHandlerFactory::getKeyboard()
{
    return KeyboardSkeleton::GetInstance();
}


/*
 * returns a local keyboard
 */
Timer * LocalEventHandlerFactory::getTimer()
{
    return TimerSkeleton::GetInstance();
}


/*
 * returns a local keyboard
 */
Mouse * LocalEventHandlerFactory::getMouse()
{
    return MouseSkeleton::GetInstance();
}


/*
 * Returns a local reshaper
 */
Reshape * LocalEventHandlerFactory::getReshape()
{
    return ReshapeSkeleton::GetInstance();
}


/*
 * private constructor
 */
LocalEventHandlerFactory::LocalEventHandlerFactory()
{}

}

