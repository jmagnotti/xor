#include "InputEventHandlerFactory.h"

namespace XOR {

// set the singleton to NULL 
InputEventHandlerFactory * InputEventHandlerFactory::_inputEventHandlerFactory = NULL;

/*
 * Accessor
 */
InputEventHandlerFactory * InputEventHandlerFactory::GetInstance()
{
    if (_inputEventHandlerFactory == NULL)
        _inputEventHandlerFactory = new InputEventHandlerFactory();

    return _inputEventHandlerFactory;
}


/*
 * returns a multicast receiving keyboard
 */
Keyboard * InputEventHandlerFactory::getKeyboard()
{
    return KeyboardSkeleton::GetInstance();
}


/*
 * returns a multicast agnostic timer
 */
Timer * InputEventHandlerFactory::getTimer()
{
    //#FIXME
    return TimerStub::GetInstance();
}


/*
 * returns a multicast receiving mouse
 */
Mouse * InputEventHandlerFactory::getMouse()
{
    return MouseSkeleton::GetInstance();
}


/*
 * private constructor
 */
InputEventHandlerFactory::InputEventHandlerFactory()
{}

}

