#ifndef LOCALEVENTHANDLERFACTORY_H
#define LOCALEVENTHANDLERFACTORY_H


#include "EventHandlerFactory.h"

#include "keyboard/Keyboard.h"
#include "keyboard/KeyboardSkeleton.h"
#include "mouse/Mouse.h"
#include "mouse/MouseSkeleton.h"
#include "reshape/Reshape.h"
#include "reshape/ReshapeSkeleton.h"
#include "timer/Timer.h"
#include "timer/TimerSkeleton.h"


namespace XOR {

/**
 * This factory receives mouse and keyboard input from the multicast socket.
 * The timer and reshaper are local and do not listen to their respective
 * multicast groups. This factory should be paired with the InputEventProxyFactory.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class InputEventHandlerFactory : public EventHandlerFactory 
{

public:

    /**
     * Singleton Accessor
     */
    static InputEventHandlerFactory * GetInstance();


    /**
     * Returns a multicast receiving KeyboardSkeleton
     */
    Keyboard * getKeyboard();


    /**
     * Returns a multicast receiving MouseSkeleton
     */
    Mouse * getMouse();


    /**
     * Returns a local, multicast agnostic TimerSkeleton
     */
    Timer * getTimer();


    /**
     * Returns a local, multicast agnostic ReshapeSkeleton
     */
    Reshape * getReshape();


private:

    InputEventHandlerFactory();

    static InputEventHandlerFactory * _inputEventHandlerFactory;

};

}

#endif          // LOCALEVENTHANDLERFACTORY_H

