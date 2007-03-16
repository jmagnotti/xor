#include "Viewer.h"

namespace XOR {

// initialize static defaults
const char * Viewer::DEFAULT_WINDOW_TITLE	= "Project Xavier | 2.0 alpha";

const double Viewer::DEFAULT_FOV		= 60;
const double Viewer::DEFAULT_NEAR_CLIP	= 0.01f;
const double Viewer::DEFAULT_FAR_CLIP	= 10000.0f;

const int Viewer::DEFAULT_WINDOW_X		= 200;
const int Viewer::DEFAULT_WINDOW_Y		= 100;

const int Viewer::DEFAULT_WINDOW_WIDTH	= 900;
const int Viewer::DEFAULT_WINDOW_HEIGHT	= 825;

const int 	 Viewer::DEFAULT_COLOR_DEPTH   = 32;
const Uint32 Viewer::DEFAULT_VIDEO_FLAGS   = SDL_OPENGL | SDL_RESIZABLE;

const int Viewer::WALL_MODE_NONE      = 0;
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
	_size = new Dimension2D(winWidth, winHeight);

	_title = windowTitle;

	_fullscreen         = fullscreen;

	_fieldOfView		= fov;
	_nearClippingPlane	= nearCP;
	_farClippingPlane	= farCP;

	_wallXoffset		= 0;
	_wallYoffset		= 0;
	_wallMode			= WALL_MODE_NONE;

	_offsetBase			= 0.0025;
	_offsetModifier		= 2.0;
	_fovBase			= 0.25;
	_fovModifier		= 2.0;

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
World * Viewer::setModel(World * rend)
{
    World * old_model = _model;

	_model = rend;

    return old_model;
}


/* 
 * Returns the window size
 */
Dimension2D * Viewer::getWindowSize()
{
	return _size->clone();
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
    setupClearColor(); 

    glViewport(0, 0, (int)_size->getWidth(), (int)_size->getHeight());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	// METHOD #1 : tiled display wall adjustment
	if (_wallMode == WALL_MODE_STANDARD) {
		float moffset = _offsetBase;
		float aoffset = moffset / _offsetModifier;

		glFrustum(	(float)_wallXoffset * moffset - aoffset,
					(float)_wallXoffset * moffset + aoffset,
					(float)_wallYoffset * moffset - aoffset,
					(float)_wallYoffset * moffset + aoffset,
					_nearClippingPlane,
					_farClippingPlane
				);
	}

	// METHOD #2 : perspective-based wall adjustment
	else if (_wallMode == WALL_MODE_IMMERSIVE) {
		float fovmodifier = _fovBase;
		float rotmodifier = _fieldOfView*fovmodifier*_fovModifier;

		gluPerspective(_fieldOfView*fovmodifier, (float)_size->getWidth()/
				(float)_size->getHeight(), _nearClippingPlane, _farClippingPlane);

		glPushMatrix();
		glRotatef(-(float)_wallYoffset*rotmodifier, 1.0, 0.0, 0.0);
		glRotatef( (float)_wallXoffset*rotmodifier, 0.0, 1.0, 0.0);
	}
	
	// no wall adjustment
	else {
		gluPerspective(_fieldOfView, 
				(float)_size->getWidth()/ (double)_size->getHeight(), 
				_nearClippingPlane, _farClippingPlane);
	}

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
CoordinateSystem * Viewer::setCoordinateSystem(CoordinateSystem * coordinateSystem)
{
    CoordinateSystem * old = _coordinateSystem;
    _coordinateSystem = coordinateSystem;

    return old;
}


/*
 * Returns the current full screen status
 */
bool Viewer::isFullScreen()
{
    return _fullscreen;
}

Vector3D * Viewer::toScreenCoordinates(Vector3D * worldCoord)
{
    GLint viewport[4];
    GLdouble mvmatrix[16], projmatrix[16];
    GLdouble sx, sy, sz;

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

    gluProject((GLdouble) worldCoord->getX(), worldCoord->getY(),
               (GLdouble) worldCoord->getZ(), mvmatrix, projmatrix, viewport,
               &sx, &sy, &sz);

    return new Vector3D((float) sx, (float) sy, (float) sz);
}


/*
 * 
 */
Vector3D * Viewer::toWorldCoordinates(Vector3D * screenCoord)
{
    GLint real_y;
    GLdouble wx, wy, wz;
    GLint viewport[4];
    GLdouble mvmatrix[16], projmatrix[16];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

    //real_y = viewport[3] - (GLint) screenCoord->getY() - 1;

    gluUnProject((GLdouble) screenCoord->getX(), screenCoord->getY(),
                (GLdouble) screenCoord->getZ(), mvmatrix, projmatrix, viewport,
                &wx, &wy, &wz);

    return new Vector3D((float) wx, (float) wy, (float) wz);
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
	delete _size;
    _size = size->clone();

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
    handleReshape(ReshapeEvent::ConstructInstance(_size));

    /*
    SDL_Event reshape = { SDL_VIDEORESIZE };
    reshape.resize.w = (int) _size->getX();
    reshape.resize.h = (int) _size->getY();

    SDL_PushEvent(&reshape);
    */
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
	//ReshapeEvent * evt = ReshapeEvent::ConstructInstance(getWindowSize());
	//handleReshape(evt);
	forceReshape();
}


/**
 * Change the wall setup offset base
 */
void Viewer::incrementWallViewOffsetBase(float change)
{
	_offsetBase += change;
	forceReshape();
	cout << "  offset base: " << _offsetBase << endl;
}


/**
 * Change the wall setup offset modifier
 */
void Viewer::incrementWallViewOffsetModifier(float change)
{
	_offsetModifier += change;
	forceReshape();
	cout << "  offset modifier: " << _offsetModifier << endl;
}


/**
 * Change the wall setup field of view base
 */
void Viewer::incrementWallViewFovBase(float change)
{
	_fovBase += change;
	forceReshape();
	cout << "  fov base: " << _fovBase << endl;
}


/**
 * Change the wall setup field of view modifier
 */
void Viewer::incrementWallViewFovModifier(float change)
{
	_fovModifier += change;
	forceReshape();
	cout << "  fov modifier: " << _fovModifier << endl;
}


/*
 * set wall mode
 */
void Viewer::setWallMode(int mode)
{
	if (mode == WALL_MODE_STANDARD) {
		_wallMode = WALL_MODE_STANDARD;
		cout << "  new wall mode: standard" << endl;
	}
	else if (mode == WALL_MODE_IMMERSIVE) {
		_wallMode = WALL_MODE_IMMERSIVE;
		cout << "  new wall mode: immersive" << endl;
	}
	else {
		_wallMode = WALL_MODE_NONE;
		cout << "  new wall mode: none" << endl;
	}
	forceReshape();
}


}

