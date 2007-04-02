#include "Camera.h"

namespace XOR {

// initialize static defaults
const double Camera::DEFAULT_FOV		= 60;
const double Camera::DEFAULT_NEAR_CLIP	= 0.01f;
const double Camera::DEFAULT_FAR_CLIP	= 10000.0f;

const int 	 Camera::DEFAULT_COLOR_DEPTH   = 32;
const Uint32 Camera::DEFAULT_VIDEO_FLAGS   = SDL_OPENGL | SDL_RESIZABLE;

const int Camera::WALL_MODE_NONE      = 0;
const int Camera::WALL_MODE_STANDARD  = 1;
const int Camera::WALL_MODE_IMMERSIVE = 2;


/*
 * default constructor
 */ 
Camera::Camera()
{
    build(DEFAULT_FOV, DEFAULT_NEAR_CLIP, DEFAULT_FAR_CLIP, 
          DEFAULT_COLOR_DEPTH, DEFAULT_VIDEO_FLAGS, WALL_MODE_NONE, 
          new Vector2D(0,0), Color::DARK_NAVY); 
}


Camera::Camera (double fov, double nearCP, double farCP, 
                int colorDepth, Uint32 videoFlags, int wallMode, 
                Vector2D * offset, const float color[4])
{
    build (fov, nearCP, farCP, colorDepth, 
           videoFlags, wallMode, offset, color);
}


/*
 * set up the viewer
 */
void Camera::build (double fov, double nearCP, double farCP, 
                    int colorDepth, Uint32 videoFlags, int wallMode, 
                    Vector2D * offset, const float color[4])
{
	_fieldOfView		= fov;
	_nearClippingPlane	= nearCP;
	_farClippingPlane	= farCP;

    _colorDepth  = colorDepth;
    _videoFlags  = videoFlags;

    _fullscreen  = false;

    if (_videoFlags & SDL_FULLSCREEN == SDL_FULLSCREEN)
        _fullscreen  = true;

	_wallXoffset		= offset->getX();
	_wallYoffset		= offset->getY();
	_wallMode			= wallMode;

    //Mike Lam's Magic Numbers
        _offsetBase			= 0.0025f;
        _offsetModifier		= 2.0f;
        _fovBase			= 0.25f;
        _fovModifier		= 2.0f;
    //---

	_coordinateSystem = CoordinateSystemFactory::GetDefaultCoordinateSystem();

    for(int i=0; i<4; i++)
        _backgroundColor[i] = color[i];
}


/*
 * Destructor
 */
Camera::~Camera()
{
    delete _coordinateSystem;
}


/*
 * Sets the model to be viewed.
 * This is substitutive, not additive.
 */
World * Camera::setModel(World * rend)
{
    World * old_model = _model;

	_model = rend;

    return old_model;
}


/*
 * timer tick
 */
void Camera::handleTick()
{
    view();
}


/*
 * 
 */
void Camera::handleReshape(ReshapeEvent * event)
{
    // reset clear color
    setupClearColor(); 

    glViewport(0, 0, event->getWidth(), event->getHeight());

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

		gluPerspective(_fieldOfView*fovmodifier, (float)event->getWidth()/
				(float)event->getHeight(), _nearClippingPlane, _farClippingPlane);

        // don't need this at the base level of the projection matrix
        //glPushMatrix();   

		glRotatef(-(float)_wallYoffset*rotmodifier, 1.0, 0.0, 0.0);
		glRotatef( (float)_wallXoffset*rotmodifier, 0.0, 1.0, 0.0);
	}
	
	// no wall adjustment
	else {
		gluPerspective(_fieldOfView, 
				(float)event->getWidth() / (float)event->getHeight(), 
				_nearClippingPlane, _farClippingPlane);
	}

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


/*
 * reshape the camera manually
 */
void Camera::handleReshape(int width, int height)
{
   handleReshape(ReshapeEvent::ConstructInstance(new Dimension2D(width, height))); 
}


/*
 * add listener
 */
void Camera::addListener(CameraListener * cl)
{
    _listeners.push_back(cl);
}


/*
 * remove listener
 */
void Camera::removeListener(CameraListener * cl)
{
    bool removed = false;

    list<CameraListener*>::iterator iter   = _listeners.begin();
    list<CameraListener*>::iterator finish = _listeners.end();

    while (!removed && iter != finish) {
        if (*iter == cl) {
            _listeners.erase(iter);
            removed = true;
		}
		else {
			++iter;
		}
    }
}


/*
 * notify everyone of the movement
 */
void Camera::notifyListeners()
{
    Vector3D * pos = getBaseVector()->clone();

    list<CameraListener*>::iterator iter   = _listeners.begin();
	list<CameraListener*>::iterator next   = _listeners.begin();
    list<CameraListener*>::iterator finish = _listeners.end();

    while (iter != finish) {
		++next;
		(*iter)->handleCameraMove(pos);
        iter = next;
    }

    delete pos;
}


/*
 * reset the SDL surface
 */
void Camera::setupSDLVideo(Dimension2D * size)
{
    SDL_SetVideoMode((int)size->getWidth(), (int)size->getHeight(), _colorDepth, _videoFlags);
}


/*
 * SDL is reseting this value for me, so we have to set it back each time.
 */
void Camera::setupClearColor()
{
    glClearColor(_backgroundColor[0], _backgroundColor[1], 
                 _backgroundColor[2], _backgroundColor[3]);
}


/*
 * make main rendering call
 */
void Camera::view()
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
 * set fullscreen
 */
void Camera::setFullScreen(bool status)
{
	// TODO: implement turning fullscreen ON/OFF

	if (status != _fullscreen) {
        if (status)
            
        _fullscreen = status;
    }

}


/*
 * Change user coordinate system.
 */
CoordinateSystem * Camera::setCoordinateSystem(CoordinateSystem * coordinateSystem)
{
    CoordinateSystem * old = _coordinateSystem;
    _coordinateSystem = coordinateSystem;

    return old;
}


/*
 * Returns the current full screen status
 */
bool Camera::isFullScreen()
{
    return _fullscreen;
}

Vector3D * Camera::toScreenCoordinates(Vector3D * worldCoord)
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
Vector3D * Camera::toWorldCoordinates(Vector3D * screenCoord)
{
    //GLint real_y;
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
void Camera::toggleFullScreen()
{
    setFullScreen(!isFullScreen()); 
}


/*
 * Sets the size of the window, copies values, so be sure to free this dimension object if you created it.
void Camera::setWindowDimension(Dimension2D * size)
{
	delete _size;
    _size = size->clone();

    SDL_SetVideoMode((int)_size->getWidth(), (int)_size->getHeight(),
            DEFAULT_COLOR_DEPTH, DEFAULT_VIDEO_FLAGS);
}
 */ 


/*
 * sets the color to be used for glClearColor(..)
 */
void Camera::setBackground(const float color[4])
{
    for (int i=0; i<4; i++)
        _backgroundColor[i] = color[i];

    setupClearColor();
}



/*
 * increment wall node position
 */
void Camera::incrementWallOffset(int x, int y)
{
	setWallOffset(_wallXoffset + x, _wallYoffset + y);
}


/*
 * set wall node position
 */
void Camera::setWallOffset(int x, int y)
{
	_wallXoffset = x;
	_wallYoffset = y;

	cout << "new x offset: " << _wallXoffset << endl;
	cout << "new y offset: " << _wallYoffset << endl;

	// We have the force reshape method above that was created for Controller to for an initial reshape
	// without having to know how to constrct events.
	//ReshapeEvent * evt = ReshapeEvent::ConstructInstance(getWindowSize());
	//handleReshape(evt);
    Window::ForceReshape();
}


/**
 * Change the wall setup offset base
 */
void Camera::incrementWallViewOffsetBase(float change)
{
	_offsetBase += change;
    Window::ForceReshape();
	cout << "  offset base: " << _offsetBase << endl;
}


/**
 * Change the wall setup offset modifier
 */
void Camera::incrementWallViewOffsetModifier(float change)
{
	_offsetModifier += change;
    Window::ForceReshape();
	cout << "  offset modifier: " << _offsetModifier << endl;
}


/**
 * Change the wall setup field of view base
 */
void Camera::incrementWallViewFovBase(float change)
{
	_fovBase += change;
    Window::ForceReshape();
	cout << "  fov base: " << _fovBase << endl;
}


/**
 * Change the wall setup field of view modifier
 */
void Camera::incrementWallViewFovModifier(float change)
{
	_fovModifier += change;
    Window::ForceReshape();
	cout << "  fov modifier: " << _fovModifier << endl;
}


/*
 * set wall mode
 */
void Camera::setWallMode(int mode)
{
    if (mode >= WALL_MODE_NONE && mode <= WALL_MODE_IMMERSIVE) {
        _wallMode = mode;

        // for debugging
        if (_wallMode == WALL_MODE_STANDARD)
            cout << "  new wall mode: standard" << endl;
        else if (_wallMode == WALL_MODE_IMMERSIVE)
            cout << "  new wall mode: immersive" << endl;
        else
            cout << "  new wall mode: none" << endl;

        Window::ForceReshape();
    }
}

}

