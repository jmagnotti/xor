#ifndef FULLEVENTPROXYFACTORY_H
#define FULLEVENTPROXYFACTORY_H 

#include "EventHandlerFactory.h"

#include "reshape/Reshape.h"
#include "reshape/ReshapeSkeleton.h"
#include "keyboard/Keyboard.h"
#include "keyboard/KeyboardStub.h"
#include "mouse/Mouse.h"
#include "mouse/MouseStub.h"
#include "timer/Timer.h"
#include "timer/TimerStub.h"

namespace XOR {

/**
 * This factory returns stubs for Keyboard, Mouse, and Timer. This factory
 * SHOULD NOT be used when running another non FullEventProxyFactory because of
 * some issues with multiple GL contexts. The exact nature of the failure is
 * not known, only that the other app crashes during the Viewer::view() method.
 * The safer alternative at the moment is the InputEventProxyFactory, that
 * sends KeyEvents and MouseEvents only.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class FullEventProxyFactory : public EventHandlerFactory
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


    /**
	 * Returns multicast agnostic ReshapeSkeleton
     */
    Reshape * getReshape();

private:

    FullEventProxyFactory();

    static FullEventProxyFactory * _fullEventProxyFactory;

};

}

#endif          // FULLEVENTPROXYFACTORY_H


