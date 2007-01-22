#ifndef REMOTE_EVENT_FACTORY_H
#define REMOTE_EVENT_FACTORY_H


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
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class RemoteEventHandlerFactory : public EventHandlerFactory
{

public:

    /**
     * Singleton Accessor
     */
    static RemoteEventHandlerFactory * GetInstance();


    /**
     *
     */
    Keyboard * getKeyboard();


    /**
     *
     */
    Mouse * getMouse();


    /**
     *
     */
    Timer * getTimer();


    /**
     *
     */
    Reshape * getReshape();

private:

    RemoteEventHandlerFactory();

    static RemoteEventHandlerFactory * _remoteEventHandlerFactory;

};

}

#endif          // REMOTE_EVENT_FACTORY_H

