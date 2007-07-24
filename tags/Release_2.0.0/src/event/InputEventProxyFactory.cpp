#include "InputEventProxyFactory.h"


namespace XOR {

// set the singleton to NULL 
InputEventProxyFactory * InputEventProxyFactory::_inputEventProxyFactory = NULL;

/*
 * Singleton Accessor
 */
InputEventProxyFactory * InputEventProxyFactory::GetInstance()
{
    if (_inputEventProxyFactory == 0)
        _inputEventProxyFactory = new InputEventProxyFactory();

    return _inputEventProxyFactory;
}


/*
 * returns a local keyboard
 */
Keyboard * InputEventProxyFactory::getKeyboard()
{
    return KeyboardStub::GetInstance();
}


/*
 * returns a local, multicast agnostic timer
 */
Timer * InputEventProxyFactory::getTimer()
{
//#FIXME
    return TimerStub::GetInstance();
}


/*
 * returns a multicasting mouse
 */
Mouse * InputEventProxyFactory::getMouse()
{
    return MouseStub::GetInstance();
}


/*
 * private constructor
 */
InputEventProxyFactory::InputEventProxyFactory()
{}

}

