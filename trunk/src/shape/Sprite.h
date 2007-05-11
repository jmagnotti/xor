#ifndef SPRITE_H
#define SPRITE_H


#include "../core/Controller.h"
#include "../event/timer/TimerListener.h"
#include "SpriteListener.h"


namespace XOR {

/**
 * Do NOT create any sprites before initializing the Controller, since
 * sprites need timer support.
 *
 * @author John Magnotti
 * @version 1.0
 */
class Sprite : public TimerListener
{

public:

    /**
	 * Destructor removes the sprite from the timer's observer list
	 */
    virtual ~Sprite();


    /**
	 * Constructor adds the sprite to the timer's observer list
	 */
    Sprite();


	/**
	 * adds a listener that will be updated when the sprite's position
	 * changes
	 */
	void addListener(SpriteListener * sl);

	/**
	 * removes a listener
	 */
	void removeListener(SpriteListener * sl);


    /**
	 * called by the timer
	 */
    void handleTick();


	/**
	 * This method will be called when the timer fires.
	 */
	virtual void endFrame()=0;


	/**
	 * starts the timer listening 
	 */
	virtual void begin();


	/**
	 * stops the timer listening
	 */
	void end();

	/**
	 * Returns the id of the sprite. used for labelling sprites that may
	 * be of different concrete child types.
	 */
	int getID();


protected:

	void notifyListeners();

	int _id;

	static int _idCounter;
};

}

#endif			// SPRITE_H

