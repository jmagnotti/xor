#ifndef INPUTEVENTPROXYFACTORY_H
#define INPUTEVENTPROXYFACTORY_H


#include "EventHandlerFactory.h"

#include "keyboard/Keyboard.h"
#include "keyboard/KeyboardStub.h"
#include "mouse/Mouse.h"
#include "mouse/MouseStub.h"
#include "timer/Timer.h"
#include "timer/TimerStub.h"

namespace XOR {

/**
 * Proxies only Keyboard and Mouse input. Does NOT listen to Timer
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class InputEventProxyFactory : public EventHandlerFactory 
{

public:

    /**
     * Singleton Accessor
     */
    static InputEventProxyFactory * GetInstance();


    /**
     * Returns a multicasting KeyboardStub
     */
    Keyboard * getKeyboard();


    /**
     * Returns a multicasting MouseStub
     */
    Mouse * getMouse();


    /**
	 * Returns a multicast agnostic TimerSkeleton
     */
    Timer * getTimer();


private:

    InputEventProxyFactory();

    static InputEventProxyFactory * _inputEventProxyFactory;

};

}

#endif          // LOCALEVENTHANDLERFACTORY_H

