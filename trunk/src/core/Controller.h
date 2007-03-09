#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <iostream>
#include <stdlib.h>
#include <vector>

// SDL is the new kid in town
#include "../../include/SDL.h"

// sub-controllers
#include "../event/EventHandlerFactory.h"
#include "../event/keyboard/Keyboard.h"
#include "../event/mouse/Mouse.h"
#include "../event/timer/Timer.h"
#include "../event/reshape/Reshape.h"

// model
#include "World.h"
#include "../shape/Point3D.h"
#include "../shape/Renderable.h"
#include "../shape/Object3D.h"
#include "../shape/Renderable.h"

// view
#include "Viewer.h"


using namespace std;

namespace XOR {

/**
 * This is the main controller. Be sure that only controller logic goes in
 * here.
 */
class Controller
{

public:

	/**
	 * Destructor
	 */
	virtual ~Controller();


	//TODO this caused insurmountable problems with circular dependencies. The
	//XavierConfiguration object will always supply an EventHandlerFactory, so
	//should you for now.
    /**
	 *
     * Used internally by other classes to get a handle on the active
     * controller instance. This is seen as cleaner than a global instance, but
     * is functinally equivalent. Application developers should prefer the
     * parameterized version of this accessor unless you can guarantee it has
     * already been called.
	static Controller * GetInstance();
     */


	/**
	 * Returns an instance of the controller
	 */
	static Controller * GetInstance(EventHandlerFactory * factory);
    //static Controller * GetInstance(XavierConfiguration * configuration);


	/**
	 * Calls destructors and terminates by calling exit(0)
	 */
	static void CleanUpAndExit();


	/**
	 * Sets up SDL, sub-controllers, and a view
	 * with sensible defaults
	 */
	void defaultConfiguration(bool configGL=true);


    /**
     * Default openGL parameters
     */
    void defaultGLConfiguration();

	
    /**
     * Separate out the SDL_GL vars so they can be reset on a reshape event
     */
    void defaultSDLGLConfiguration();


	/** 
	 * Returns a reference to the model.
     * If you try to get the model before you have set one, NULL is returned
	 */
	World * getModel();


	/** 
	 * Returns a reference to the view.
     * If you try to get the viewer before you have set one, NULL is returned
	 */
	Viewer * getViewer();


    /**
     * Returns a reference to the current Keyboard. This should always be
     * preferred over the singleton accessors in KeyboardSkeleton and KeyboardStub,
     * since this method is (rightfully) agnostic of the event factory being used. 
     */
	Keyboard * getKeyboard();

	
    /**
     * Returns a reference to the current Mouse. This should always be
     * preferred over the singleton accessors in MouseSkeleton and MouseStub,
     * since this method is (rightfully) agnostic of the event factory being used. 
     */
	Mouse * getMouse();


    /**
     * Returns a reference to the current Reshape. This should always be
     * preferred over the singleton accessors in ReshapeSkeleton and ReshapeStub,
     * since this method is (rightfully) agnostic of the event factory being used. 
     */
    Reshape * getReshape();


    /**
     * Returns a reference to the current timer. This should always be
     * preferred over the singleton accessors in TimerSkeleton and TimerStub,
     * since this method is (rightfully) agnostic of the event factory being used. 
     */
    Timer * getTimer();


	/**
	 * Starts the main loop.
	 */
	void run();


	/**
	 * Specifies the model for the controller to use.
     * This can be a World object or not. The framework automatically wraps the
     * Renderable inside of a World object if it isn't one. The comparison is
     * very particular, it compares this renderable with the renderable from
     * World::GetInstance(), this is to ensure that only one World object
     * exists at a time. World could be refactored into a Universe if you want
     * to have multiple worlds.  
     */
	Renderable *  setModel(Renderable*);


	/**
	 * Specifies the view for the controller to use
     * Note that the viewer is also responsible for handling reshapes (Viewer
     * IS-A ReshapeListener), so be sure that the handleReshape() method
     * behaves appropriately
	 */
	Viewer * setViewer(Viewer*);


    /**
     * Since the controller is setting up a key listener, we need to have a way
     * for the user to override this guy.
    void removeDefaultKeyboardListener();
     */


    /**
     * Since the controller is setting up a mouse listener, we need to have a
     * way for the user to override this guy.
    void removeDefaultMouseListener();
     */


    /**
     * Event loop, it's an SDL thing
     */
    static void EventLoop();


private:

	Keyboard *	    _keyboard;
	Mouse *		    _mouse;
	Reshape *	    _reshape;
	Timer *		    _timer;

	Renderable *      _model;
	Viewer *	    _viewer;

	Controller();

	Controller(EventHandlerFactory * factory);

    /**
     * the real exit function
     */
    static void exit();

	static Controller *	_controller;
    
};

}

#endif			// CONTROLLER_H

