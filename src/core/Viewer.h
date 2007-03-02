#ifndef VIEWER_H
#define VIEWER_H


#include <vector>

#include "../../include/SDL.h"
#include "../../include/SDL_opengl.h"

#include "World.h"

#include "../paint/Color.h"
#include "../geometry/Dimension2D.h"
#include "../transform/Transformable.h"
#include "../transform/CoordinateSystem.h"
#include "../transform/CoordinateSystemFactory.h"
#include "../event/timer/TimerListener.h"
#include "../event/reshape/ReshapeListener.h"
#include "../event/reshape/ReshapeEvent.h"

namespace XOR {


/**
 * Designed to maintain the state of the camera of the world.
 * The Viewer is doing a little bit too much windowing at the moment.
 */
class Viewer : public ReshapeListener, public TimerListener, public Transformable
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

	static const int		WALL_MODE_NONE;
	static const int		WALL_MODE_STANDARD;
	static const int		WALL_MODE_IMMERSIVE;


    /**
     * default constructor. Uses constants above.
     */
    Viewer();


	/**
     * Explicit Constructor
     * 
     * @param fov		Field of view
     * @param nearCP	Near clipping plane
     * @param farCP		Far clipping plane
     */
    Viewer(double fov, double nearCP, double farCP);


	/** 
	 * Destructor
	 */
	~Viewer();


	Dimension3D * getDimension() {return NULL;}
	Vector3D * getBaseVector() {return NULL;}

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
    void handleReshape(ReshapeEvent * event);


    /**
     * Simple reshape handler
     */
    void handleReshape(int width, int height);


    /**
     * redraw the screen on tick events
     */
     void handleTick();


	/** 
	 * Calls render() on the model
	 */
	virtual void view(void);


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
	CoordinateSystem * setCoordinateSystem(CoordinateSystem * coordinateSystem);
	

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


	/**
	 * Change the video wall offset by a given increment.
	 */
	void incrementWallOffset(int x, int y);
	

	/**
	 * Change the video wall offset.
	 */
	void setWallOffset(int x, int y);


	/**
	 * Change the wall view partitioning mode.
	 */
	void setWallMode(int mode);


    /**
     * Returns a vector representing the world position in Screen coordinates.
     */
    Vector3D * toScreenCoordinates(Vector3D * worldCoord);


    /**
     * Returns a vector representing the screen position in world coordinates.
     */
    Vector3D * toWorldCoordinates(Vector3D * screenCoor);
    
	
protected:

    CoordinateSystem * _coordinateSystem;

private:

    // set all state vars
    void initialize(double fov, double nearCP, double farCP, int winWidth, int
            winHeight, bool fullscreen, const char * windowTitle);

    double			_nearClippingPlane;	
    double			_farClippingPlane;
	double			_fieldOfView;

	int				_wallXoffset;
	int				_wallYoffset;
	int				_wallMode;

	bool			_fullscreen;

    float           _backgroundColor[3];
    const char *    _title;

	Dimension2D *	_size;

	World *	_model;


};

}

#endif          //VIEWER_H
