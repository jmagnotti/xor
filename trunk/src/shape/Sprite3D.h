#ifndef SPRITE3D_H
#define SPRITE3D_H


#include "../core/Controller.h"
#include "../event/timer/TimerListener.h"
#include "Sprite3DListener.h"

namespace XOR {

/**
 * Do NOT create any sprites before initializing the Controller, since
 * sprites need timer support.
 *
 * @author John Magnotti
 * @version 1.0
 */
class Sprite3D : public Object3D, public TimerListener
{

public:

    /**
	 * Destructor removes the sprite from the timer's observer list
	 */
    virtual ~Sprite3D();


    Sprite3D();

	/**
	 * decorating constructor
	 */
    Sprite3D(Object3D * object);


	/**
	 * adds a listener that will be updated when the sprite's position
	 * changes
	 */
	void addListener(Sprite3DListener * sl);

	/**
	 * removes a listener
	 */
	void removeListener(Sprite3DListener * sl);


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
	 * declared virtual to allow for other labelling mechanisms
	 */
	virtual int getID();


protected:

	void notifyListeners();

	int _id;

	static int _idCounter;
	list <Sprite3DListener*> _listeners;
};

}

#endif			// SPRITE3D_H

