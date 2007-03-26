#include "FullEventProxyFactory.h"

namespace XOR {

// set the singleton to NULL 
FullEventProxyFactory * FullEventProxyFactory::_fullEventProxyFactory = NULL;

/*
 * Accessor
 */
FullEventProxyFactory * FullEventProxyFactory::GetInstance()
{
    if (_fullEventProxyFactory == 0)
        _fullEventProxyFactory = new FullEventProxyFactory();

    return _fullEventProxyFactory;
}


/*
 * returns a multicasting keyboard
 */
Keyboard * FullEventProxyFactory::getKeyboard()
{
    return KeyboardStub::GetInstance();
}


/*
 * returns a multicasting timer
 */
Timer * FullEventProxyFactory::getTimer()
{
    return TimerStub::GetInstance();
}


/*
 * returns a multicasting mouse
 */
Mouse * FullEventProxyFactory::getMouse()
{
    return MouseStub::GetInstance();
}


/*
 * private constructor
 */
FullEventProxyFactory::FullEventProxyFactory()
{}

}

