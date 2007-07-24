#ifndef GAME_H
#define GAME_H

#include "../../xor.h"

#include "BrickCollection.h"
#include "BrickParser.h"
#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameSpace.h"

using namespace XOR; 

class GameState;

/**
 * Class that functions as the game Controller. Game is a singleton that encapsulates several
 * states using the state pattern. Currently reperesented states are Ready, Play, Win, and Lose.
 * Several other states are possible such as Pause, but they have been omitted in this inital
 * implementation for simplicity's sake. State or context switches are performed using the
 * setState() method, which is called whenever an event occurs that changes the state of the
 * game, such as the player winning. Each state has and in() and out() method that handle the
 * configuration of the Game for that particular state. All state/context transition tasks,
 * including the calls to in() and out() are handled by the switch state method.
 *
 * @pattern State Pattern: 
 */
class Game
{
public:

	/**
	 * Returns a pointer to the Game singleton. This method
	 * will instantiate the singleton on the initial method call with 
	 * context == state and returns a pointer to the object. If the 
	 * singleton has already been instantiated, the method returns a 
	 * pointer to the current instance of the game and disregards the
	 * context supplied by state
	 */
	static Game * GetInstance();


	/**
	 * Destructor. Not actually functional because the objects contained
	 * in the model will be deleted by the model's destructor.
	 */
	~Game();


	/**
	 * Switches the Game context to state. During the switch, the previous 
	 * context's out() method is called to perform any necessary cleanup 
	 * and/or transitionary tasks. state's in() method is called after the 
	 * switch to perform any setup and/or transitionary tasks that lead 
	 * into the new context. The new context should enter a "clean"  
	 * environment, that is, it is critical that each context clean up after
	 * itself (turn of what it turned on) and this behavior should NOT be 
	 * altered. This way, each new context only has to be concerned with 
	 * setting up the things it needs to run and not cleaning up any garbage
	 * from the previous context.
	 *
	 * @param state - the state to set
	 */
	void setState(GameState * state);


	/**
	 * Equivalent to the system exit command, Exit deletes _game and calls
	 * the Controller's CleanUpAndExit() method.
	 */
	static void Exit();

	Ball * getBall();
	Paddle * getPaddle();


private:

	friend class GameState;
	friend class PlayState;
	friend class ReadyState;

	/**
	 * Explicit constructor for the Game singleton. If there is no game already
	 * created, it instantiates one with state as the inital context and returns
	 * a pointer to that instance. If a game is already instantiated, it returns
	 * a pointer to the current instance. The constructor is ONLY called by the
	 * getInstance method
	 */
	Game();


	/**
	 * Any listeners that Game uses to process events should be added here.
	 * This method should only be called by the default constructor.
	 */
	void initializeListeners();


	/**
	 * Objects whos models are to be rendered in the Game go here.
	 * This method should only be called by the default constructor.
	 */
	void addModelsToWorld();
	
	//attributes
	static Game * _game;

	GameState * _state;

	Ball   * _ball;
	Paddle * _paddle;

	GameSpace * _gameSpace;

	BrickCollection * _bricks;


};


#endif			// GAME_H

