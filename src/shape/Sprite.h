#ifndef SPRITE_H
#define SPRITE_H


#include "../core/Controller.h"
#include "../event/timer/TimerListener.h"


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
	 * called by the timer
	 */
    void handleTick();


	/**
	 * This method will be called when the timer fires.
	 */
	virtual void endFrame()=0;

};

}

#endif			// SPRITE_H

