#include "Game.h"

class GameConfig : public XavierConfiguration { EventFactory * getEventFactory()
	{
		return InputEventHandlerFactory::GetInstance();
	} bool isGLDepthTestEnabled()
	{
		return true;
	}

	bool isGLAntiAliasEnabled()
	{
		return true;
	}

	bool isGLBlendEnabled()
	{
		return true;
	}

	unsigned int getTimerInterval()
	{
		return 40;
	}

	bool isGLFogEnabled()
	{
		return false;
	}

};




Game * Game::_game = NULL;


/*
 * destructor
 */
Game::~Game()
{}


/*
 * singleton accessor
 */
Game * Game::GetInstance()
{
	if (_game == NULL)
		_game = new Game();
	
	return _game;	
}


/* * bail
 */
void Game::Exit()
{
	if (_game != NULL) {
		delete _game;
		Controller::GetInstance()->CleanUpAndExit();
	}
}

/*
 *
 */
Game::Game()
{
	_state = NULL;

	Controller * ctrl = Controller::GetInstance(new GameConfig());

	// adds renderables to the world object collection
	addModelsToWorld();
}


/*
 * set the new context to state
 */
void Game::setState(GameState * state)
{
	cout << "setting game state" << endl;

	//old context clean up
	if (_state != NULL)
		_state->out();	

	//new context set
	_state = state;
	//new context setup
	_state->in();
}

Ball * Game::getBall()
{
	return _ball;
}

Paddle * Game::getPaddle()
{
	return _paddle;
}


/*
 * add game objects to the world
 */
void Game::addModelsToWorld()
{
	_ball		= new Ball(new Vector3D(10,1,1), 0.1);
	_gameSpace	= new GameSpace(new Dimension3D(30.0f, 3.0f, 30.f), _ball);
	_paddle		= new Paddle(new RectangularPrism(new Vector3D(10,1,.5),
					new Dimension3D(2.0,2.0,2.0), new Paint(Color::ORANGE)),
					30, _ball);

	_bricks = BrickParser::GetInstance("bricks.brk")->parse(_ball); 

	Controller::GetInstance()->setModel(_gameSpace);

	World * world = Controller::GetInstance()->getModel();
	world->addObject("ball",   _ball);
	world->addObject("paddle", _paddle);
	world->addObject("bricks", _bricks);

	Controller::GetInstance()->getKeyboard()->addListener(new DefaultKeyboardListener());
}


