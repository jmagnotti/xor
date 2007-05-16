#ifndef BRICKCOLLECTION_H
#define BRICKCOLLECTION_H


#include <vector>
#include "../../xor.h"
#include "HitListener.h"
#include "Brick.h"
#include "Ball.h"


using namespace XOR;

/**
 * A collection of brick objects that go into the gamespace
 */
class BrickCollection : public Object3D, public HitListener, public Sprite3DListener
{

public:

	/**
	 * Builds a new brick collection. For now it needs a reference to
	 * the ball so it can do collision detection
	 */
    BrickCollection(Ball * ball);

	/**
	 * Destructor
	 */
    ~BrickCollection();

	/**
	 * Add a brick object to the collection
	 *
	 * @param brick - the brick to add
	 */
    void addBrick(Brick * brick);

	/**
	 * Remove a brick object from the collection
	 *
	 * @param brick - the brick to remove
	 */
    void removeBrick(Brick * brick);


	/**
	 * Render the collection by iterating through
	 * it and calling each brick's render method
	 */
    void render();
	// don't call this
    void renderObject();


	/**
	 * Returns the origin vector of the brick collection
	 *
	 * @return Vector3D *
	 */
    Vector3D * getBaseVector();


	/**
	 * Returns the dimsensions of the brick collection
	 *
	 * @return Dimension3D *
	 */
    Dimension3D * getDimension();


	/**
	 * If a brick is hit by the ball, it notifies the collection by
	 * calling this method with itself as the parameter
	 *
	 * @param brick - the brick that was hit
	 */
    void handleHit(Brick * brick);


	/**
	 * Called when the ball moves. not sure who should be doing this;
	 */
	void handlePositionChange(Vector3D * position, int id);


private:
	
	Ball * _ball;
	vector<Brick*> _bricks;
};


#endif			// BRICKCOLLECTION_H

