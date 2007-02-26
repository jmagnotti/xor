#include "Controller.h"


namespace XOR {

// Set the static instances to null
Controller * Controller::_controller = NULL;

/*
 * Private Default Constructor
 */
Controller::Controller()
{}


/*
 * Private Explicit Constructor
 */
Controller::Controller(EventHandlerFactory * factory)
{
    //cout << "Building Controller" << endl;
    // reshape must be created before Viewer, since viewer is going to add
    // itself as a listener
	_reshape     = factory->getReshape();

	//set up the controllers
    _timer       = factory->getTimer();
	_mouse       = factory->getMouse();
	_keyboard    = factory->getKeyboard();

	//set the default keyboard listener
    //_keyboard->addListener(DefaultKeyboardListener::GetInstance());

	//set the default mouse listener
	//_mouse->addListener(DefaultMouseListener::GetInstance());

	_viewer = new Viewer();

	_reshape->addListener(_viewer);
    _timer->addListener(_viewer);
}


/*
 * Destructor
 */
Controller::~Controller()
{
    // model
    delete _model;

    // view
    delete _viewer;

    // sub-controllers
    delete _keyboard;
    delete _mouse;

    delete _reshape;
    delete _timer;
}


/* 
 * Singleton Accessor
Controller * Controller::GetInstance()
{
	if (_controller == NULL)
		_controller = new Controller(EventHandlerFactory::GetDefaultFactory());

	return _controller;
}
 */

Controller * Controller::GetInstance(EventHandlerFactory * factory)
{
	if (_controller == NULL)
		_controller = new Controller(factory);

	return _controller;
}

/*
 * does the real deleting, protected to keep people from calling it
 * directly
 */
void Controller::exit()
{
	//FIXME
	Controller * control = Controller::GetInstance(NULL);
	delete control;

	//TODO need a <list> of shutdown listeners so controller doesn't have to do
	//it all

    // clean up SDL, and exit
    SDL_Quit(); 
}


/*
 * Push a quit event onto the queue
 */
void Controller::CleanUpAndExit()
{
    SDL_Event quitEvent = {SDL_QUIT}; 
    SDL_PushEvent(&quitEvent);
}


/*
 * unhoses the SDL GL bridge
 */
void Controller::defaultSDLGLConfiguration()
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); 
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  16);

    // supposedly this is only needed on non-OS X setups
    // set the framebuffer size for R,G,B, & A
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    _viewer->setupSDLVideo();
}


/* 
 * Set up the default configuration for SDL
 */
void Controller::defaultConfiguration(bool configGL)
{
    //SDL_Init(SDL_INIT_EVERYTHING); 
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO); 

    defaultSDLGLConfiguration();

    if (configGL)
        defaultGLConfiguration();
}


/*
 * Set up openGL defaults
 */
void Controller::defaultGLConfiguration()
{
	// set the clear color
    _viewer->setupClearColor();

    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);

	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// enable anti-aliasing
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// enable depth testings
	// this messes some things up with Alpha blended objects
	glEnable(GL_DEPTH_TEST);

	// enable fog

	//glEnable(GL_FOG);

	glFogi(GL_FOG_MODE, GL_LINEAR);

	// the hint has to be GL_NICEST, else large quads aren't shaded correctly
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogi(GL_FOG_START, 0);
	glFogi(GL_FOG_END, 25);
	GLfloat fogColor[4] = {0.0, 0.0, 0.0, 1.0};
	glFogfv(GL_FOG_COLOR, fogColor);
}


/* 
 * Returns the model
 */
World * Controller::getModel()
{
	return (World*)_model;
}


/*
 * Returns the view
 */
Viewer * Controller::getViewer()
{
    if (_viewer == NULL)
        cout << "NULL VIEWER" << endl;
	return _viewer;
}


/*
 * Returns the keyboard
 */
Keyboard * Controller::getKeyboard()
{
	return _keyboard;
}


/*
 * Returns the mouse
 */
Mouse * Controller::getMouse()
{
	return _mouse;
}


/*
 * Returns the reshape handler
 */
Reshape * Controller::getReshape()
{
    return _reshape;
}


/*
 * returns the timer
 */
Timer * Controller::getTimer()
{
    return _timer;
}


/*
 * Starts the program loop
 */
void Controller::run(void)
{
    _viewer->forceReshape();

    // start ticking
    _timer->start();

    //set final window properties
    // _viewer->setWindowDimension();
    //_viewer->setupClearColor();

    // sit around and wait for something to do 
    Controller::EventLoop();
}


/* 
 * sets the model for the controller
 */
Object3D * Controller::setModel(Object3D * model)
{
    Object3D * old_model = _model;

	// In order to do proper rendering, we need a world object
	// we don't want to force people to do all that though, so we do a quick check
	// and wrap the renderable inside a world object if it isn't a world object
	// note that if the object IS a world object, then we don't apply our special rotation
	if (! (World::IsWorldObject(model)) )
		_model = World::GetInstance(model);
	else // it already is a world object
		_model = model;

	_viewer->setModel((World*)_model);

    return old_model;
}

/*
 * sets the viewer for the controller
 */
Viewer * Controller::setViewer(Viewer * viewer)
{
    Viewer * old_viewer = _viewer;

    viewer->setModel(getModel());

    getTimer()->removeListener(_viewer);
    getReshape()->removeListener(_viewer);

    _viewer = viewer;

    getTimer()->addListener(_viewer);
    getReshape()->addListener(_viewer);

    return old_viewer;
}


/**
 * set mouse listener
void Controller::removeDefaultMouseListener()
{
    _mouse->removeListener(DefaultMouseListener::GetInstance()); 
}
 */


/**
 * set keyboard listener
void Controller::removeDefaultKeyboardListener()
{
    _keyboard->removeListener(DefaultKeyboardListener::GetInstance());
}
 */


/*
 * Monolithic event loop.
 */
void Controller::EventLoop()
{
    SDL_Event event;
	//FIXME
    Controller * ctrl = Controller::GetInstance(NULL);

    // we are using WaitEvent(...) because we want everything to be called
    // off timer ticks or other events.
    while(SDL_WaitEvent(&event)) {

        switch(event.type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                ctrl->getKeyboard()->generateKeyEvent(&event);
                break;

            case SDL_MOUSEMOTION:
                ctrl->getMouse()->move(&event);
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                ctrl->getMouse()->click(&event);
                break;

            case SDL_VIDEORESIZE:
                ctrl->getReshape()->generateEvent(&event);

                // attempting to reset GL info that may be getting hosed 
                // by SDL deleting the SDL_Surface we are rendering to
                // this may be dirtier than adding ctrl as a ReshapeListener,
                // but works for now.
                ctrl->defaultSDLGLConfiguration();
                ctrl->defaultGLConfiguration();
                break;

            case SDL_QUIT:
                exit();
                break;

            case SDL_USEREVENT:
                if (event.user.code == Timer::TIMER_TICK_EVENT) {
                    ctrl->getTimer()->tickTock();
                }
                else {
                    // establish user event system here
                    // ctrl->getUserEventPublisher()->publish(&event);
                }
                break;

			default: cout << "Unknown event occured" << endl;	break;
        }

    }   // end while 

}   // end EventLoop

}

