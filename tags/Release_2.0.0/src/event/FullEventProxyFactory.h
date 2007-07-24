#ifndef FULLEVENTPROXYFACTORY_H
#define FULLEVENTPROXYFACTORY_H 

#include "EventFactory.h"

#include "keyboard/Keyboard.h"
#include "keyboard/KeyboardStub.h"
#include "mouse/Mouse.h"
#include "mouse/MouseStub.h"
#include "timer/Timer.h"
#include "timer/TimerStub.h"

namespace XOR
{

/**
 * This factory returns stubs for Keyboard, Mouse, and Timer. 
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class FullEventProxyFactory : public EventFactory
{

public:

    /**
     * Singleton Accessor
     */
    static FullEventProxyFactory * GetInstance();

    /**
     * Returns a multicasting KeyboardStub
     */
    Keyboard * getKeyboard();

    /**
     * Returns a multicasting MouseStub
     */
    Mouse * getMouse();

    /**
     * Returns a multicasting TimerStub
     */
    Timer * getTimer();

private:

    FullEventProxyFactory();

    static FullEventProxyFactory * _fullEventProxyFactory;

};

}

#endif          // FULLEVENTPROXYFACTORY_H
