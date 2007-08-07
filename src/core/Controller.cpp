#include "Controller.h"
namespace XOR
{

// Set the static instance to null
Controller * Controller::_controller= NULL;

/*
 * Private Default Constructor
 */
Controller::Controller()
{
}

/*
 * Private Explicit Constructor
 */
Controller::Controller(XavierConfiguration * configuration)
{
	_configuration = configuration;

    EventFactory * factory = _configuration->getEventFactory();

    //set up the event generators
    _timer = factory->getTimer();

    Timer::SetInterval(_configuration->getTimerInterval());

    _mouse = factory->getMouse();

    _keyboard = factory->getKeyboard();

    _window = new Window(_configuration->getWindowPosition(),
            _configuration->getWindowSize(), (char*)(_configuration->getWindowTitle()));

    _camera = new Camera(
            _configuration->getFieldOfView(),
            _configuration->getNearClip(),
            _configuration->getFarClip(),
            _configuration->getColorDepth(),
            _configuration->getVideoFlags(),
            _configuration->getWallMode(),
            _configuration->getWallOffset(),
            _configuration->getBackgroundColor()
    );

    _window->addListener(_camera);
    _timer->addListener(_camera);

	defaultSDLGLConfiguration();
	defaultGLConfiguration();
}

/*
 * Destructor
 */
Controller::~Controller()
{
    // model
    delete _model;

    // view
    delete _camera;

    // sub-controllers
    delete _keyboard;
    delete _mouse;

    delete _window;
    delete _timer;
}

/* 
 * Singleton Accessor
 */
Controller * Controller::GetInstance()
{
    if (_controller == NULL)
        _controller = new Controller(new XavierConfiguration());

    return _controller;
}

Controller * Controller::GetInstance(XavierConfiguration * configuration)
{
    if (_controller == NULL)
        _controller = new Controller(configuration);

    return _controller;
}

/*
 * does the real deleting, protected to keep people from calling it
 * directly
 */
void Controller::exit()
{
    Controller * control = Controller::GetInstance();
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
    SDL_Event quitEvent = { SDL_QUIT };
    SDL_PushEvent(&quitEvent);
}

/*
 * unhoses the SDL GL bridge
 */
void Controller::defaultSDLGLConfiguration()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    _camera->setupSDLVideo(getWindow()->getSize());

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    // supposedly this is only needed on non-OS X setups
    // set the framebuffer size for R,G,B, & A
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
}


/*
 * Set up openGL defaults
 */
void Controller::defaultGLConfiguration()
{
    // set the clear color
    _camera->setupClearColor();

	glShadeModel(_configuration->getGLShadeModel());

    // enable blending
	if (_configuration->isGLTextureEnabled())
		glEnable(GL_TEXTURE_2D);
	if (_configuration->isGLBlendEnabled()) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	if (_configuration->isGLAntiAliasEnabled()) {
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	}

	if (_configuration->isGLDepthTestEnabled())
		glEnable(GL_DEPTH_TEST);

	if (_configuration->isGLFogEnabled()) {
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, _configuration->getGLFogMode());
		glHint(GL_FOG_HINT, GL_NICEST);
		glFogi(GL_FOG_START,  _configuration->getGLFogStart());
		glFogi(GL_FOG_END,    _configuration->getGLFogEnd());
		glFogfv(GL_FOG_COLOR, _configuration->getGLFogColor());
	}

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
Camera * Controller::getCamera()
{
    return _camera;
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
 * Returns the window handler
 */
Window * Controller::getWindow()
{
    return _window;
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
	_camera->handleReshape((int) _window->getSize()->getWidth(),
			(int)_window->getSize()->getHeight());

    // start ticking
    _timer->start();

    // sit around and wait for something to do 
    Controller::EventLoop();
}

/* 
 * sets the model for the controller
 */
Renderable * Controller::setModel(Renderable * model)
{
    // In order to do proper rendering, we need a world object
    // we don't want to force people to do all that though, so we do a quick check
    // and wrap the renderable inside a world object if it isn't a world object
    if (! (World::IsWorldObject(model)))
        _model = World::GetInstance(model);
    else
        // it already is a world object
        _model = model;

    return _camera->setModel((World*)_model);
}

/*
 * sets the viewer for the controller
 */
Camera * Controller::setCamera(Camera * cam)
{
    Camera * old_camera = _camera;

    cam->setModel(getModel());

    getTimer()->removeListener(_camera);
    getWindow()->removeListener(_camera);

    _camera = cam;

    getTimer()->addListener(_camera);
    getWindow()->addListener(_camera);

    return old_camera;
}

/*
 * Monolithic event loop.
 */
void Controller::EventLoop()
{
    SDL_Event event;

    Controller * ctrl = Controller::GetInstance();

    // we are using WaitEvent(...) because we want everything to be called
    // off timer ticks or other events.
    while (SDL_WaitEvent(&event))
    {

        switch (event.type) {

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
                ctrl->getWindow()->generateEvent(&event);

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

            default:
                break;
        }

    } // end while 

} // end EventLoop

}

