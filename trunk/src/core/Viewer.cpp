#include "Viewer.h"

namespace XOR {

// initialize static defaults
const char * Viewer::DEFAULT_WINDOW_TITLE	= "Project Xavier | 2.0 alpha";

const int   Viewer::DEFAULT_FOV			= 60;
const float Viewer::DEFAULT_NEAR_CLIP	= .01f;
const int   Viewer::DEFAULT_FAR_CLIP	= 100;

const int Viewer::DEFAULT_WINDOW_X		= 200;
const int Viewer::DEFAULT_WINDOW_Y		= 100;

const int Viewer::DEFAULT_WINDOW_WIDTH	= 800;
const int Viewer::DEFAULT_WINDOW_HEIGHT	= 525;

const int Viewer::DEFAULT_COLOR_DEPTH   = 0;    // use the OS default
const int Viewer::DEFAULT_VIDEO_FLAGS   = SDL_OPENGL | SDL_RESIZABLE;


/*
 * Explicit Constructor
 */
Viewer::Viewer(int fov, float nearCP, float farCP)
{
	_size = new Dimension2D(DEFAULT_WINDOW_WIDTH, 
							DEFAULT_WINDOW_HEIGHT);

	_fullscreen         = false;

	_fieldOfView		= fov;
    _nearClippingPlane	= nearCP;
    _farClippingPlane	= farCP;

	// camera orientation
	_orientation = new Orientate();
	for (int o = 0; o < 3; o++)
		_coordinates[o] = new Rotate();

    for(int i=0; i<3; i++)
        _backgroundColor[i] = Color::DARK_BLUE[i];
}


/*
 * Destructor
 */
Viewer::~Viewer()
{
    delete _size;
    delete _orientation;

	for (int o = 0; o < 3; o++) {
        delete _coordinates[o];
    }
}


/*
 * Sets the model to be viewed.
 * This is substitutive, not additive.
 */
void Viewer::setModel(Renderable * rend)
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
 * handles window reshapes
 */
void Viewer::handleReshape(SDL_Event * event)
{
    // set a new video size
	_size->setWidth(event->resize.w);
	_size->setHeight(event->resize.h);

    // new screen size & bg color
    setupSDLVideo();

    // reset clear color
    setupClearColor(); 

    glViewport(0, 0, (int)_size->getWidth(), (int)_size->getHeight());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	gluPerspective(_fieldOfView, (double)_size->getWidth()/ (double)_size->getHeight(),
		_nearClippingPlane, _farClippingPlane);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


/*
 * reset SDL surface
 */
void Viewer::setupSDLVideo()
{
    //at some point we need to have variables to hold things like current video flags, etc.
    SDL_SetVideoMode(_size->getWidth(), _size->getHeight(), 
                                    DEFAULT_COLOR_DEPTH, DEFAULT_VIDEO_FLAGS);
}


/*
 * SDL is reseting this value for me, so we have to set it back each time. We need to have a better way of
 */
void Viewer::setupClearColor()
{
	glClearColor(_backgroundColor[0], _backgroundColor[1], _backgroundColor[2], 1.0f); 
}


/*
 * make main rendering call
 */
void Viewer::view()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// since we're technically moving the whole world, push the inverse
	_orientation->pushInverse();

	for (int o = 0; o < 3; o++)
		_coordinates[o]->push();
	
	_model->render();

	for (int o = 2; o >= 0; o--)
		_coordinates[o]->pop();
		
	_orientation->pop();

    //SDL call to swap the off screen buffer with the on screen one
    SDL_GL_SwapBuffers(); 
}


/*
 * Sets the title on the window
 */
void Viewer::setWindowTitle(char * text)
{
    SDL_WM_SetCaption("Project Xavier", "XOR");
}


/*
 * set fullscreen
 */
void Viewer::setFullScreen(bool status)
{
	// TODO: implement turning fullscreen OFF

	if (status && !_fullscreen)
        int i=0;

	_fullscreen = status;
}


/*
 * change user coordinate system.
 * Should use strategy Pattern.
 */
void Viewer::setCoordinateSystem(bool math)
{
	if (math) {
		for (int o = 0; o < 3; o++)
			delete _coordinates[o];

		_coordinates[0] = new Rotate(90.0f,0,1,0);
		_coordinates[1] = new Rotate(90.0f,1,0,0);
		_coordinates[2] = new Rotate(0.0f,0,0,0);
	}
	else {
		for (int o = 0; o < 3; o++) {
			delete _coordinates[o];
			_coordinates[o] = new Rotate(0.0f,0,0,0);
		}
	}
}


/*
 * Returns the current camera orientation transform
 */
Orientate * Viewer::getOrientation()
{
    return _orientation;
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

    // this should trigger a reshape event
    SDL_SetVideoMode(_size->getWidth(), _size->getHeight(), DEFAULT_COLOR_DEPTH, DEFAULT_VIDEO_FLAGS);
}


/*
 * sets the color to be used for glClearColor(..)
 */
void Viewer::setBackground(const float color[3])
{
    for (int i=0; i<3; i++)
        _backgroundColor[i] = color[i];
}

}

