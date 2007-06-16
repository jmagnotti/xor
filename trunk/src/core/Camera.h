#ifndef VIEWER_H
#define VIEWER_H


#include <list>

#include "../../include/SDL.h"
#include "../../include/SDL_opengl.h"

#include "World.h"
#include "Window.h"
#include "CameraListener.h"

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
 * The Camera is doing a little bit too much windowing at the moment.
 */
class Camera : public ReshapeListener, public TimerListener, public Transformable
{

public:

	static const double		DEFAULT_FOV;
	static const double		DEFAULT_NEAR_CLIP;
	static const double		DEFAULT_FAR_CLIP;

	static const int        DEFAULT_COLOR_DEPTH;
	static const Uint32     DEFAULT_VIDEO_FLAGS;

	static const int		WALL_MODE_NONE;
	static const int		WALL_MODE_STANDARD;
	static const int		WALL_MODE_IMMERSIVE;


    /**
     * default constructor. Uses constants above.
     */
    Camera();


	/**
     * Explicit Constructor
     * 
     * @param fov		Field of view
     * @param nearCP	Near clipping plane
     * @param farCP		Far clipping plane
     */
    Camera (double fov, double nearCP, double farCP, int colorDepth, 
            Uint32 videoFlags, int wallMode, Vector2D * offset, const float color[4]);


	/** 
	 * Destructor
	 */
	~Camera();


    /**
     * Add a listener to the collection
     */
    void addListener(CameraListener * cl);


    /**
     * Removes the given listener from the collection if it exists
     */
    void removeListener(CameraListener * cl);


    /**
     * This could return the screen coordinates or something cool
     */
	inline Dimension3D * getDimension() {return NULL;}


    /**
     * this could return the bottom left world coord.
     */
	inline Vector3D * getBaseVector() {return NULL;}

	/**
	 * Set the renderable to the viewer
	 */
	World * setModel(World*);


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
    void setupSDLVideo(Dimension2D * size);


    /*
     * Recalculate the clearColor since SDL keeps messing it up. This is kind
     * of a hack, but 
     * it allows for a somewhat clean way of doing it, at least people don't
     * have to make the GL
     * call themselves, right?
     */
    void setupClearColor();


	/**
	 * Change the video wall offset by a given increment.
	 */
	void incrementWallOffset(int x, int y);
	

	/**
	 * Change the video wall offset.
	 */
	void setWallOffset(int x, int y);


	/**
	 * Change the wall setup offset base
	 */
	void incrementWallViewOffsetBase(float change);


	/**
	 * Change the wall setup offset modifier
	 */
	void incrementWallViewOffsetModifier(float change);


	/**
	 * Change the wall setup field of view base
	 */
	void incrementWallViewFovBase(float change);


	/**
	 * Change the wall setup field of view modifier
	 */
	void incrementWallViewFovModifier(float change);


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
    Vector3D * toWorldCoordinates(Vector3D * screenCoord);
    
	
protected:

    CoordinateSystem * _coordinateSystem;


    /**
     * Sends out the camera's position to all the listeners.
     */
    void notifyListeners();


private:

    // set all state vars
void build (double fov, double nearCP, double farCP, int colorDepth, Uint32 videoFlags, int wallMode, Vector2D * offset, const float color[4]);

    double			_nearClippingPlane;	
    double			_farClippingPlane;
	double			_fieldOfView;

	int				_wallXoffset;
	int				_wallYoffset;
	int				_wallMode;

	double			_offsetBase;
	double			_offsetModifier;
	double			_fovBase;
	double			_fovModifier;

	bool			_fullscreen;

    float           _backgroundColor[4];

	World *	_model;

	int        _colorDepth;
	Uint32     _videoFlags;

    list<CameraListener*> _listeners;

    SDL_Event _reshape;
};

}

#endif          //VIEWER_H

