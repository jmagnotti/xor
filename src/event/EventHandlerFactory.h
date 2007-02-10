#ifndef EVENTHANDLERFACTORY_H
#define EVENTHANDLERFACTORY_H


#include "keyboard/Keyboard.h"
#include "mouse/Mouse.h"
#include "timer/Timer.h"
#include "reshape/Reshape.h"


namespace XOR {

/**
 * Interface for Event Factories. Simplifies creation of remote
 * (stub) or local (skeleton) event generator. 
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class EventHandlerFactory
{

public:


    /**
     *
     */
    virtual Keyboard * getKeyboard()=0;


    /**
     *
     */
    virtual Mouse * getMouse()=0;


    /**
     *
     */
    virtual Timer * getTimer()=0;


    /**
     *
     */
    virtual Reshape * getReshape()=0;


};

}

#endif          // EVENTHANDLERFACTORY_H
