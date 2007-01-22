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
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class LocalEventHandlerFactory : public EventHandlerFactory 
{

public:

    /**
     * Singleton Accessor
     */
    static LocalEventHandlerFactory * GetInstance();


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

    LocalEventHandlerFactory();

    static LocalEventHandlerFactory * _localEventHandlerFactory;

};

}

#endif          // LOCALEVENTHANDLERFACTORY_H

