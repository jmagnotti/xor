#ifndef REMOTE_EVENT_FACTORY_H
#define REMOTE_EVENT_FACTORY_H

#include "EventFactory.h"

#include "keyboard/Keyboard.h"
#include "keyboard/KeyboardSkeleton.h"
#include "mouse/Mouse.h"
#include "mouse/MouseSkeleton.h"
#include "timer/Timer.h"
#include "timer/TimerSkeleton.h"

namespace XOR
{

/**
 * The handler compliment to FullEventProxyFactory. Generates handlers that
 * will receive Keyboard, Mouse, and Timer events. Window events are still
 * handled locally, with no multicast receiving. Note that in using this
 * factory no local SDL_Timer is created, so the first frame (and subsequent
 * frames) is not displayed until it is received through the multicast group.
 * This means that the app will display a black screen.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class FullEventHandlerFactory : public EventFactory
{

public:

    /**
     * Singleton Accessor
     */
    static FullEventHandlerFactory * GetInstance();

    /**
     * Returns a multicast receiving KeyboardSkeleton
     */
    Keyboard * getKeyboard();

    /**
     * Returns a multicast receiving MouseSkeleton
     */
    Mouse * getMouse();

    /**
     * Returns a multicast receiving TimerSkeleton
     */
    Timer * getTimer();

private:

    FullEventHandlerFactory();

    static FullEventHandlerFactory * _fullEventHandlerFactory;

};

}

#endif          // REMOTE_EVENT_FACTORY_H
