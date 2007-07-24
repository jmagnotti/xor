#ifndef BRICK_H
#define BRICK_H

#include "../../xor.h"
#include "HitListener.h"
#include "Ball.h"

class HitListener;

using namespace XOR;

/**
 * The brick class represents any of the objects that the ball can react with apart from the
 * hull that describes the gamespace and the paddle that the player controls. Using the 
 * Observer pattern, the objects of this class publish hit events to subscribers such as the 
 * brick array or the scoring engine so that appropriate actions may be performed by the 
 * listeners such as turning off collision and rendering for a hit brick or adding points to
 * the score. The addListener and removeListener methods allow the list of HitListeners to be
 * updated during runtime.
 */
class Brick : public RectangularPrism
{

public:

	// brick type constants
	static const int BREAKABLE = 1;
	static const int OTHER_TYPE = 2;

	Brick(Vector3D * position, Dimension3D * size, Paint * paint);
	virtual ~Brick();

	/**
	 * Adds HitListener objects to the _listeners list
	 *
	 * @param hl - the HitListener to add
	 */
	void addListener(HitListener * hl);


	/** * Removes the specified listener from _listeners
	 *
	 * @param hl - the HitListener to remove
	 */
	void removeListener(HitListener * hl);


	/**
	 * checks for collision, then call doCollide on child classes. This
	 * method makes certain assumptions about the ball's trajectory that
	 * preclude the ability to collide with more than one brick at a time,
	 * or more than one wall on a given brick. Also, this method only
	 * guarantees that the plane of the  collision will be detected, not
	 * the specific direction. For example, the method may say a collision
	 * occurred on RectangularPrism::LEFT, when the collision may have in
	 * fact occurred on RectangularPrism::RIGHT. By using the velocity of
	 * the Ball it can easily be determined which wall was struck, but
	 * this information is generally not needed.
	 */
	bool checkCollision(Ball * ball);

	virtual const int getType()=0;


protected:

	/**
	 * Called by Brick objects when they receive a hit to notify all subscribers
	 * (HitListeners) that the brick has been hit. Iterates over _listeners and
	 * calls each one's handle hit method. It may be the case that a listener
	 * removes itself from the list after its handleHit method is called; therefore,
	 * iteraters are used to ensure that handleHit is never called on a deleted
	 * object or invalid memory.
	 */
	void notifyListeners();

	/**
	 * concrete children need to decide what to do when a collision
	 * occurs.
	 */
	virtual void doCollide(const int side, Ball * ball);


private:

	list<HitListener*> _listeners;
};


#endif			// BRICK_H

