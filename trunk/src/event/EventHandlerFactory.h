#ifndef EVENTHANDLERFACTORY_H
#define EVENTHANDLERFACTORY_H


#include "keyboard/Keyboard.h"
#include "mouse/Mouse.h"
#include "timer/Timer.h"


namespace XOR {

/**
 * Interface for Event Factories. Simplifies creation of multicast sending
 * (stub) or multicast receiving (skeleton) event handlers. 
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class EventHandlerFactory
{

public:


    /**
     */
    virtual Keyboard * getKeyboard()=0;


    /**
     */
    virtual Mouse * getMouse()=0;


    /**
     */
    virtual Timer * getTimer()=0;

};

}

#endif          // EVENTHANDLERFACTORY_H

