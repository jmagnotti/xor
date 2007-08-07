#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "../../include/SDL.h"

// sub-controllers
#include "../event/EventFactory.h"
#include "../event/keyboard/Keyboard.h"
#include "../event/mouse/Mouse.h"
#include "../event/timer/Timer.h"
#include "Window.h"

// model
#include "Renderable.h"
#include "World.h"
#include "../object3D/Point3D.h"
#include "../object3D/Object3D.h"

#include "XavierConfiguration.h"

// view
#include "Camera.h"


namespace XOR {

class Camera;
class XavierConfiguration;

/**
 * This is the main controller. Be sure that only controller logic goes in
 * here.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class Controller
{

public:

	/**
	 * Destructor
	 */
	virtual ~Controller();


    /**
     * Used internally by other classes to get a handle on the active
     * controller instance. This is seen as cleaner than a global instance, but
     * is functinally equivalent. Application developers should prefer the
     * parameterized version of this accessor unless you can guarantee it has
     * already been called.
     */
	static Controller * GetInstance();


	/**
	 * Returns an instance of the controller
	 */
    static Controller * GetInstance(XavierConfiguration * configuration);


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
	Camera * getCamera();


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
     * Returns a reference to the current Window. This should always be
     * preferred over the singleton accessors in Window, since this method is
     * (rightfully) agnostic of the event factory being used. 
     */
    Window * getWindow();


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
     * Note that the viewer is also responsible for handling reshapes (Camera
     * IS-A ReshapeListener), so be sure that the handleReshape() method
     * behaves appropriately
	 */
	Camera * setCamera(Camera*);


    /**
     * SDL Event loop. This method should never be called directly by the
     * application programmer.
     */
    static void EventLoop();


private:

	Controller();

	Controller(XavierConfiguration * configuration);

    /**
     * the real exit function
     */
    static void exit();

    
	Keyboard * _keyboard;
	Mouse    * _mouse;
	Timer    * _timer;
	Window   * _window;

	Renderable * _model;
	Camera     * _camera;
	XavierConfiguration * _configuration;

	static Controller *	_controller;

};

}

#endif			// CONTROLLER_H

