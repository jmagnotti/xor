#include "ReadyState.h"

ReadyState * ReadyState::_state = NULL;

/*
 * Returns the current instance
 */
ReadyState * ReadyState::GetInstance(Game * game)
{
	if (_state == NULL)
		_state = new ReadyState();

	_state->_game = game;
	return _state;	
}

/*
 * Destructor
 */
ReadyState::ReadyState()
{}

/*
 * Destructor
 */
ReadyState::~ReadyState()
{
	delete _state;
}

/*
 * Handles user key events using the XOR framework
 */
void ReadyState::handleKeyEvent(KeyEvent * ke)
{
	std::cout << "Handling key" << endl;
    if (ke->getType() == KeyEvent::KEY_UP_EVENT)
	{
		if (ke->getKey() == SDLK_p)
		{
			Controller::GetInstance()->getCamera()->print();
		}	

		// TRANSITION TEST
		if (ke->getKey() == SDLK_g)
		{
			_game->setState(PlayState::GetInstance(_game));
		}
	}
}


/*
 * Handles timer tick events using the XOR framework
 */
void ReadyState::handleTick()
{
	//does nothing yet
}


/*
 * Handles mouse motion and mouse click events using
 * the XOR framework
 */
void ReadyState::handleMouseEvent(MouseEvent * me)
{
	//does nothing yet
}


/**
 * This method turns collision detection off, sets
 * the key and mouse listeners to ON
 */
void ReadyState::in()
{
	setKeyListen(true);	

	int time = 1500;

	Controller::GetInstance()->getMouse()->addListener(new DefaultMouseListener());

	Controller::GetInstance()->getCamera()->setTranslation(new
			Vector3D(10.4014,19.7322,-11.3612), new
			TimedInterpolation(time, NULL));
	Controller::GetInstance()->getCamera()->setRotation(Orientation::THETA,
			-180, new TimedInterpolation(time, NULL));
	Controller::GetInstance()->getCamera()->setRotation(Orientation::PHI,
			-43.0007, new TimedInterpolation(time, NULL));

	/*
	   pos_x=10.4014pos_y=19.7322pos_z=-11.3612
	   focus_x=10.4046focus_y=19.9916focus_z=-11.7289
	   theta=-180.001phi=-43.0007roll=0
	   scale_x=1scale_y=1scale_z=1

		pos_x=-12.8059pos_y=24.4943pos_z=15.7389
		focus_x=-12.8274focus_y=24.5151focus_z=15.7391
		theta=-89.9994phi=-44.0005roll=0
		focal distance=1

		pos_x=-16.4188pos_y=24.3077pos_z=15.7183
		focus_x=-14.4189focus_y=22.5997focus_z=15.7008
		theta=-90phi=-40.5006roll=0
		scale_x=1scale_y=1scale_z=1
		Handling key

		pos_x=-11.5427pos_y=24.8574pos_z=14.8653
		focus_x=-11.8611focus_y=25.2428focus_z=14.613
		theta=-90.0002phi=-49.5004roll=0
		scale_x=1scale_y=1scale_z=1
	*/
}


/**
 * Clean up before exit
 */
void ReadyState::out()
{
	setKeyListen(false);	
}

