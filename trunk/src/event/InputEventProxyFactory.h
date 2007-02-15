#ifndef INPUTEVENTPROXYFACTORY_H
#define INPUTEVENTPROXYFACTORY_H


#include "EventHandlerFactory.h"

#include "keyboard/Keyboard.h"
#include "keyboard/KeyboardStub.h"
#include "mouse/Mouse.h"
#include "mouse/MouseStub.h"
#include "reshape/Reshape.h"
#include "reshape/ReshapeSkeleton.h"
#include "timer/Timer.h"
#include "timer/TimerSkeleton.h"

namespace XOR {

/**
 * Proxies only Keyboard and Mouse input. Does NOT listen to Timer or Reshape
 * events.
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


    /**
	 * Returns a multicast agnostic ReshapeSkeleton
     */
    Reshape * getReshape();


private:

    InputEventProxyFactory();

    static InputEventProxyFactory * _inputEventProxyFactory;

};

}

#endif          // LOCALEVENTHANDLERFACTORY_H

