#ifndef VIEWER_H
#define VIEWER_H


#include <vector>

#include "../../include/SDL.h"

#include "World.h"

#include "../geometry/Dimension2D.h"
#include "../shape/Point3D.h"
#include "../transform/Positionable.h"
#include "../transform/CoordinateSystem.h"
#include "../transform/CoordinateSystemFactory.h"
#include "../event/ReshapeListener.h"

namespace XOR {


/**
 * Designed to maintain the state of the camera of the world.
 * The Viewer is doing a little bit too much windowing at the moment.
 */
class Viewer : public ReshapeListener, public Positionable
{

public:

	static const char *     DEFAULT_WINDOW_TITLE;

	static const double		DEFAULT_FOV;
	static const double		DEFAULT_NEAR_CLIP;
	static const double		DEFAULT_FAR_CLIP;

	static const int		DEFAULT_WINDOW_X;
	static const int		DEFAULT_WINDOW_Y;

	static const int		DEFAULT_WINDOW_WIDTH;
	static const int		DEFAULT_WINDOW_HEIGHT;
    
	static const int        DEFAULT_COLOR_DEPTH;
	static const Uint32     DEFAULT_VIDEO_FLAGS;


	/**
     * Explicit Constructor
     * 
     * @param fov		Field of view
     * @param nearCP	Near clipping plane
     * @param farCP		Far clipping plane
     */
    Viewer(double fov=DEFAULT_FOV, double nearCP=DEFAULT_NEAR_CLIP, double farCP=DEFAULT_FAR_CLIP);


	/** 
	 * Destructor
	 */
	~Viewer();


	/**
	 * Adds a renderable to the viewer's list
	 */
	void setModel(World*);


	/**
	 * Returns a dimension object of the windows current size
	 */
	Dimension2D * getWindowSize();


    /**
	 * Called on window reshape/resize
	 */
    void handleReshape(SDL_Event * event);


    /**
     * Simple reshape handler
     */
    void handleReshape(int width, int height);


	/** 
	 * Calls render() on the model
	 */
	void view(void);


    /**
     * Sets the size of the window. Triggers a reshape event so that everything is scaled correctly.
     */
    void setWindowDimension(Dimension2D * size); 

    
    /**
     * Sets the text of the window title bar
     * @param	text	The text that will appear on the window title bar.
     */
    void setWindowTitle(char * text);


	/**
	 * Set full screen status
	 */
	void setFullScreen(bool status);


	/**
	 * Returns the current full screen status
	 */
    bool isFullScreen();


	/**
	 * Toggle whether the view is full screen
	 */
	void toggleFullScreen();


    /**
     * Sets the clear color to use for the window
     */
    void setBackground(const float color [3]);


	/**
	 * Change user coordinate system 
	 */
	void setCoordinateSystem(CoordinateSystem * coordinateSystem);
	

    /**
     * Sets the SDL Video mode with the current values of the video vars.
     * Finer control should be added at some point.
     */
    void setupSDLVideo();


    /*
     * Recalculate the clearColor since SDL keeps messing it up. This is kind
     * of a hack, but 
     * it allows for a somewhat clean way of doing it, at least people don't
     * have to make the GL
     * call themselves, right?
     */
    void setupClearColor();


    /**
     * Called to trigger a reshape event with the current settings. Use for
     * setting up new window contexts that don't already trigger a reshape
     * event (e.g., Program Initialization).
     */
    void forceReshape();


protected:

    double			_nearClippingPlane;	
    double			_farClippingPlane;
	double			_fieldOfView;

	bool			_fullscreen;

    float           _backgroundColor[3];
    const char *    _title;

	Dimension2D *	_size;

	World *	_model;

    CoordinateSystem * _coordinateSystem;

};

}

#endif          //VIEWER_H

