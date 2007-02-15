#include "FullEventHandlerFactory.h"

namespace XOR {

// set the singleton to NULL 
FullEventHandlerFactory * FullEventHandlerFactory::_fullEventHandlerFactory = NULL;

/*
 * Accessor
 */
FullEventHandlerFactory * FullEventHandlerFactory::GetInstance()
{
    if (_fullEventHandlerFactory == 0)
        _fullEventHandlerFactory = new FullEventHandlerFactory();

    return _fullEventHandlerFactory;
}


/*
 * returns a multicast receiving keyboard
 */
Keyboard * FullEventHandlerFactory::getKeyboard()
{
    return KeyboardSkeleton::GetInstance();
}


/*
 * returns a multicast receiving timer
 */
Timer * FullEventHandlerFactory::getTimer()
{
    return TimerSkeleton::GetInstance();
}


/*
 * returns a multicast receiving mouse
 */
Mouse * FullEventHandlerFactory::getMouse()
{
    return MouseSkeleton::GetInstance();
}

/*
 * returns a local, multicast agnostic ReshapeSkeleton
 */
Reshape * FullEventHandlerFactory::getReshape()
{
    return ReshapeSkeleton::GetInstance();
}

/*
 * private constructor
 */
FullEventHandlerFactory::FullEventHandlerFactory()
{}

}

