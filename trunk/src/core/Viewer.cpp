#include "Viewer.h"

namespace XOR {

// initialize static defaults
const char * Viewer::DEFAULT_WINDOW_TITLE	= "Project Xavier | 2.0 alpha";

const double   Viewer::DEFAULT_FOV			= 45;
const double   Viewer::DEFAULT_NEAR_CLIP	= 1.0f;
const double   Viewer::DEFAULT_FAR_CLIP	= 1000;

const int Viewer::DEFAULT_WINDOW_X		= 200;
const int Viewer::DEFAULT_WINDOW_Y		= 100;

const int Viewer::DEFAULT_WINDOW_WIDTH	= 900;
const int Viewer::DEFAULT_WINDOW_HEIGHT	= 825;

const int 	 Viewer::DEFAULT_COLOR_DEPTH   = 0;    			// use the OS default
const Uint32 Viewer::DEFAULT_VIDEO_FLAGS   = SDL_OPENGL | SDL_RESIZABLE;


/*
 * Explicit Constructor
 */
Viewer::Viewer(double fov, double nearCP, double farCP)
{
	_size = new Dimension2D(DEFAULT_WINDOW_WIDTH, 
				DEFAULT_WINDOW_HEIGHT);

	_title = DEFAULT_WINDOW_TITLE;

	_fullscreen         = false;

	_fieldOfView		= fov;
	_nearClippingPlane	= nearCP;
	_farClippingPlane	= farCP;

	_coordinateSystem = CoordinateSystemFactory::GetDefaultCoordinateSystem();

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


void Viewer::handleReshape(int width, int height)
{
    // set a new video size
	_size->setWidth(width);
	_size->setHeight(height);

    // we may have to worry about regenerating textures and such

    // reset clear color
    setupClearColor(); 

    glViewport(0, 0, (int)_size->getWidth(), (int)_size->getHeight());

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

	gluPerspective(_fieldOfView, (double)_size->getWidth()/ (double)_size->getHeight(),
		_nearClippingPlane, _farClippingPlane);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}


/*
 * handles window reshapes
 */
void Viewer::handleReshape(SDL_Event * event)
{
    handleReshape(event->resize.w, event->resize.h);
}


/*
 * reset SDL surface
 */
void Viewer::setupSDLVideo()
{

    // at some point we need to have variables to hold things like current video
    // flags, etc.
    SDL_SetVideoMode((int)_size->getWidth(), (int)_size->getHeight(), 
                     DEFAULT_COLOR_DEPTH, DEFAULT_VIDEO_FLAGS);
                     
    //handleReshape((int)_size->getWidth(), (int)_size->getHeight()); 
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// since we're technically moving the whole world, push the inverse
    pushInverse();
        _coordinateSystem->push();
            _model->render();
        _coordinateSystem->pop();
    pop();

    // SDL call to swap the off screen buffer with the on screen buffer
    SDL_GL_SwapBuffers(); 
}


/*
 * Sets the title on the window
 */
void Viewer::setWindowTitle(char * text)
{
	cout << "Window title arguments ignored in this version" << endl;
    SDL_WM_SetCaption(DEFAULT_WINDOW_TITLE, "XOR");
}


/*
 * set fullscreen
 */
void Viewer::setFullScreen(bool status)
{
	// TODO: implement turning fullscreen OFF

	if (status != _fullscreen)
        int i=0;

	_fullscreen = status;
}


/*
 * Change user coordinate system.
 */
void Viewer::setCoordinateSystem(CoordinateSystem * coordinateSystem)
{
    delete _coordinateSystem;
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

}

