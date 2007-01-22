#include "Controller.h"


namespace XOR {

// Set the static instances to null
Controller * Controller::_controller = 0;

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
    // reshape must be created before Viewer, since viewer is going to add
    // itself as a listener
	_reshape     = factory->getReshape();

	//set up the controllers
    _timer       = factory->getTimer();
	_mouse       = factory->getMouse();
	_keyboard    = factory->getKeyboard();

	//set the default keyboard listener
    //DefaultKeyboardListener::GetInstance();

	//set the default mouse listener
	//DefaultMouseListener::GetInstance();
	_viewer = new Viewer();
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

    // timer is special 
    _timer->stop();
}


/* 
 * Singleton Accessor
 */
Controller * Controller::GetInstance()
{
	if (_controller == NULL)
		_controller = new Controller();

	return _controller;
}

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
	Controller * control = Controller::GetInstance();
	//delete control;

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
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

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

    // no joystick suport yet
    SDL_EventState(SDL_JOYAXISMOTION, SDL_IGNORE); 
    SDL_EventState(SDL_JOYBALLMOTION, SDL_IGNORE); 
    SDL_EventState(SDL_JOYHATMOTION,  SDL_IGNORE); 
    SDL_EventState(SDL_JOYBUTTONDOWN, SDL_IGNORE); 
    SDL_EventState(SDL_JOYBUTTONUP,   SDL_IGNORE); 

    if (configGL)
        defaultGLConfiguration();
}


/*
 * Set up openGL defaults
 */
void Controller::defaultGLConfiguration()
{
	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// enable anti-aliasing
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// set the clear color
    _viewer->setupClearColor();

	// enable depth testings
	glEnable(GL_DEPTH_TEST);

	// enable fog
	glEnable(GL_FOG);

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
void Controller::setModel(Renderable* rend)
{
	// In order to do proper rendering, we need a world object
	// we don't want to force people to do all that though, so we do a quick check
	// and wrap the renderable inside a world object if it isn't a world object
	// note that if the object IS a world object, then we don't apply our special rotation
	if (! (World::IsWorldObject(rend)) )
		_model = World::GetInstance(rend);
	else // it already is a world object
		_model = rend;

	_viewer->setModel((World*)_model);
}


/**
 * set mouse listener
 */
void Controller::removeDefaultMouseListener()
{
    _mouse->removeListener(DefaultMouseListener::GetInstance()); 
}


/**
 * set keyboard listener
 */
void Controller::removeDefaultKeyboardListener()
{
    _keyboard->removeListener(DefaultKeyboardListener::GetInstance());
}


/*
 * Okay, so I hate big case statements, but this is just how SDL works, I
 * think. I am more than open to enhancements of this situations, GLUT-style
 * callbacks?
 */
void Controller::EventLoop()
{
    SDL_Event event;
    Controller * ctrl = Controller::GetInstance();

    // we are using WaitEvent(...) because we want everything to be called
    // off timer ticks or other events. I am still not 100% sure where to 
    // put the call to render...
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

            // this is where I am doing repaints, not sure if that is correct
            case SDL_USEREVENT:
                if (event.user.code == Timer::TIMER_TICK_EVENT) {
                    ctrl->getTimer()->tickTock();
                    ctrl->getViewer()->view();
                }
                else {
                    // establish user event system here
                    // ctrl->getUserEventPublisher()->publish(&event);
                }
                break;

            default: break;
        }

    }   // end while 

}   // end EventLoop

}

