#include "Viewer.h"

namespace XOR {

// initialize static defaults
const char * Viewer::DEFAULT_WINDOW_TITLE	= "Project Xavier | 2.0 alpha";

const double   Viewer::DEFAULT_FOV			= 60;
const double   Viewer::DEFAULT_NEAR_CLIP	= 0.1f;
const double   Viewer::DEFAULT_FAR_CLIP	= 1000;

const int Viewer::DEFAULT_WINDOW_X		= 200;
const int Viewer::DEFAULT_WINDOW_Y		= 100;

const int Viewer::DEFAULT_WINDOW_WIDTH	= 900;
const int Viewer::DEFAULT_WINDOW_HEIGHT	= 825;

const int 	 Viewer::DEFAULT_COLOR_DEPTH   = 32;
const Uint32 Viewer::DEFAULT_VIDEO_FLAGS   = SDL_OPENGL | SDL_RESIZABLE;

const int Viewer::WALL_MODE_STANDARD  = 1;
const int Viewer::WALL_MODE_IMMERSIVE = 2;


/*
 * default constructor
 */ 
Viewer::Viewer()
{
    initialize( DEFAULT_FOV, DEFAULT_NEAR_CLIP, DEFAULT_FAR_CLIP,
                DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, false,
                DEFAULT_WINDOW_TITLE); 
}


/*
 * Explicit Constructor
 */
Viewer::Viewer(double fov, double nearCP, double farCP)
{
    initialize(fov, nearCP, farCP, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT,
            false, DEFAULT_WINDOW_TITLE); 
}


/*
 * set up the viewer
 */
void Viewer::initialize(double fov, double nearCP, double farCP, int winWidth, int
        winHeight, bool fullscreen, const char * windowTitle)
{
    //cout << "constructing D2D from viewer" << endl;
	_size = new Dimension2D(winWidth, winHeight);

	_title = windowTitle;

	_fullscreen         = fullscreen;

	_fieldOfView		= fov;
	_nearClippingPlane	= nearCP;
	_farClippingPlane	= farCP;

	_wallXoffset		= 0;
	_wallYoffset		= 0;
	_wallMode			= WALL_MODE_STANDARD;

	_coordinateSystem = CoordinateSystemFactory::GetDefaultCoordinateSystem();

    cout << "init bg color" << endl;
    for(int i=0; i<3; i++)
        _backgroundColor[i] = Color::DARK_NAVY[i];
}


/*
 * Destructor
 */
Viewer::~Viewer()
{
    delete _size;
    delete _coordinateSystem;
}


/*
 * Sets the model to be viewed.
 * This is substitutive, not additive.
 */
void Viewer::setModel(World * rend)
{
	_model = rend;
}


/* 
 * Returns the window size
 */
Dimension2D * Viewer::getWindowSize()
{
	return _size;
}



/*
 * timer tick
 */
void Viewer::handleTick()
{
    view();
}


/*
 * 
 */
void Viewer::handleReshape(ReshapeEvent * event)
{
    // set a new video size
	_size->setWidth(event->getWidth());
	_size->setHeight(event->getHeight());

    // reset clear color
	cout << "Setting up clear color" << endl;
    setupClearColor(); 

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glViewport(0, 0, (int)_size->getWidth(), (int)_size->getHeight());


	// METHOD #1 : tiled display wall adjustment
	if (_wallMode == WALL_MODE_STANDARD) {
		double moffset = 0.025;
		double aoffset = moffset / 2.0;

		glFrustum(	(double)_wallXoffset * moffset - aoffset,
					(double)_wallXoffset * moffset + aoffset,
					(double)_wallYoffset * moffset - aoffset,
					(double)_wallYoffset * moffset + aoffset,
					_nearClippingPlane,
					_farClippingPlane
				);
	}

	// METHOD #2 : perspective-based wall adjustment
	else if (_wallMode == WALL_MODE_IMMERSIVE) {
		double fovmodifier = 0.25;
		double rotmodifier = _fieldOfView*fovmodifier*2.0;

		gluPerspective(_fieldOfView*fovmodifier, (double)_size->getWidth()/
				(double)_size->getHeight(), _nearClippingPlane, _farClippingPlane);

		glPushMatrix();
		glRotatef(-(double)_wallYoffset*rotmodifier, 1.0, 0.0, 0.0);
		glRotatef( (double)_wallXoffset*rotmodifier, 0.0, 1.0, 0.0);
	}

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}


/*
 * reset SDL surface
 */
void Viewer::setupSDLVideo()
{
    cout << "SetVideoMode" << endl;

    // at some point we need to have variables to hold things like current video
    // flags, etc.
    SDL_SetVideoMode((int)_size->getWidth(), (int)_size->getHeight(), 
                     DEFAULT_COLOR_DEPTH, DEFAULT_VIDEO_FLAGS);
                     
    setWindowTitle(NULL);

}


/*
 * SDL is reseting this value for me, so we have to set it back each time.
 */
void Viewer::setupClearColor()
{
    glClearColor(_backgroundColor[0], _backgroundColor[1], _backgroundColor[2],
            1.0f); 
}


/*
 * make main rendering call
 */
void Viewer::view()
{
	SDL_Surface * surface = SDL_GetVideoSurface();
	if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    glLoadIdentity();

	// since we're technically moving the whole world, push the inverse
    pushInverse();
		_coordinateSystem->push();
            _model->render();
        _coordinateSystem->pop();
    pop();

	if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);

    // SDL call to swap the off screen buffer with the on screen buffer
    SDL_GL_SwapBuffers(); 

}


/*
 * Sets the title on the window
 */
void Viewer::setWindowTitle(char * text)
{
    SDL_WM_SetCaption(DEFAULT_WINDOW_TITLE, "XOR");
}


/*
 * set fullscreen
 */
void Viewer::setFullScreen(bool status)
{
	// TODO: implement turning fullscreen ON/OFF

	if (status != _fullscreen)
        int i=0;

	_fullscreen = status;
}


/*
 * Change user coordinate system.
 */
void Viewer::setCoordinateSystem(CoordinateSystem * coordinateSystem)
{
    _coordinateSystem = coordinateSystem;
}


/*
 * Returns the current full screen status
 */
bool Viewer::isFullScreen()
{
    return _fullscreen;
}


/*
 * Toggle whether the view is full screen
 */
void Viewer::toggleFullScreen()
{
    setFullScreen(!isFullScreen()); 
}


/*
 * Sets the size of the window, copies values, so be sure to free this dimension object if you created it.
 */ 
void Viewer::setWindowDimension(Dimension2D * size)
{
    _size->clone(size);

    SDL_SetVideoMode((int)_size->getWidth(), (int)_size->getHeight(),
            DEFAULT_COLOR_DEPTH, DEFAULT_VIDEO_FLAGS);
}


/*
 * sets the color to be used for glClearColor(..)
 */
void Viewer::setBackground(const float color[3])
{
    for (int i=0; i<3; i++)
        _backgroundColor[i] = color[i];

    setupClearColor();
}


/*
 *
 */
void Viewer::forceReshape()
{
    SDL_Event reshape = { SDL_VIDEORESIZE };
    reshape.resize.w = (int) _size->getX();
    reshape.resize.h = (int) _size->getY();

    SDL_PushEvent(&reshape);
}


/*
 * increment wall node position
 */
void Viewer::incrementWallOffset(int x, int y)
{
	setWallOffset(_wallXoffset + x, _wallYoffset + y);
}


/*
 * set wall node position
 */
void Viewer::setWallOffset(int x, int y)
{
	_wallXoffset = x;
	_wallYoffset = y;

	cout << "new x offset: " << _wallXoffset << endl;
	cout << "new y offset: " << _wallYoffset << endl;

	// We have the force reshape method above that was created for Controller to for an initial reshape
	// without having to know how to constrct events.
	ReshapeEvent * evt = ReshapeEvent::ConstructInstance(getWindowSize());
	handleReshape(evt);
	//forceReshape();
}


/*
 * set wall mode
 */
void Viewer::setWallMode(int mode)
{
	if (mode == WALL_MODE_IMMERSIVE) {
		_wallMode = WALL_MODE_IMMERSIVE;
	}
	else {
		_wallMode = WALL_MODE_STANDARD;
	}
}


}

