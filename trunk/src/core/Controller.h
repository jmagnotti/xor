#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <iostream>
#include <stdlib.h>
#include <vector>

// SDL is the new kid in town
#include "../../include/SDL.h"

// sub-controllers
#include "../event/Keyboard.h"
#include "../event/Mouse.h"
#include "../event/Timer.h"

// model
#include "World.h"
#include "../shape/Point3D.h"
#include "../shape/Renderable.h"

// view
#include "Viewer.h"

// default listeners
#include "../event/ReshapeListener.h"
#include "../event/DefaultKeyboardListener.h"
#include "../event/DefaultMouseListener.h"

using namespace std;

namespace XOR {


/**
 * This is the main controller. Be sure that only controller 
 * logic goes in here.
 */
class Controller
{

public:

	/**
	 * Destructor
	 */
	virtual ~Controller();


	/**
	 * Returns an instance of the controller
	 */
	static Controller * GetInstance();


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
	 * Sets up a configuration for the JMU IVS (video wall)
	 * Because of the nature of the video wall, this setup is the recommended for all beginner (and 31337) users of the video wall.
	 *
	 * Be sure you have lamboot(ed) all the nodes before invoking this program
	 * -----This method just passes through to the default configurator for now------
	 */
	void defaultIVSConfiguration(bool configGL=true);


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
	 * Returns a reference to the keyboard.
	 */
	Keyboard * getKeyboard();

	
	/**
	 * Returns a reference to the mouse.
	 */
	Mouse * getMouse();


    /**
     * Returns the reshape handler
     */
    ReshapeListener * getReshapeListener();


	/**
	 * Starts the main loop.
	 */
	void run(void);


	/**
	 * Sets the initial translate of the world object.
	 */
	void setInitialPosition(Point3D*);


	/**
	 * Specifies the model for the controller to use.
	 * This can be a World object or not. The framework automatically wraps the Renderable inside of a World object if it isn't one.
	 * The comparison is very particular, it compares this renderable with the renderable from World::GetInstance(), this is to ensure
	 * that only one World object exists at a time. World could be refactored into a Universe if you want to have multiple worlds.
	 */
	void setModel(Renderable*);


	/**
	 * Specifies the view for the controller to use
	 * Note that the viewer is also responsible for handling reshapes (Viewer IS-A ReshapeListener),
	 * so be sure that the handleReshape() method behaves appropriately
	 */
	void setView(Viewer *);


    /**
     * Event loop, it's an SDL thing
     */
    static void EventLoop();


protected:

	static Controller *			_controller;


	Keyboard *			_keyboard;
	Mouse *				_mouse;
	Renderable *		_model;

	ReshapeListener *	_reshape;
	Timer *				_timer;
	Viewer *			_viewer;
    
    static bool         _keepGoing;

private:

	Controller();

};

}

#endif			// CONTROLLER_H

