#include "BrickCollection.h"
#include "BrickParser.h"

/*
 * Default Constructor
 */
BrickCollection::BrickCollection(Ball * ball)
{
	_ball = ball;
}

/*
 * Destructor
 */
BrickCollection::~BrickCollection()
{}


/*
 * add a brick to the collection
 */
void BrickCollection::addBrick(Brick * brick)
{
	_bricks.push_back(brick);
}

/*
 * remove a brick from the collection
 */
void BrickCollection::removeBrick(Brick * brick)
{
	//erase?
}


/*
 * returns the base vector
 */
Vector3D * BrickCollection::getBaseVector()
{
	return new Vector3D(0,0,0);
}

/*
 * returns the dimension
 */
Dimension3D * BrickCollection::getDimension()
{
	return new Dimension3D(1,1,1);
}

/*
 * handles a collision with the ball
 */
void BrickCollection::handleHit(Brick * brick)
{}

void BrickCollection::handlePositionChange(Vector3D * position, int id)
{
	vector<Brick*>::iterator iter 	= _bricks.begin();
	vector<Brick*>::iterator finish = _bricks.end();

	bool collide = false;
	while(iter != finish && !collide) {

		//FIXME -- HACK
		if (Brick::BREAKABLE == (*iter)->getType()) {
			// only checkCollision if the render flag is set
			BreakableBrick * brick = (BreakableBrick*)(*iter);
			if (! brick->isBroken())
				collide = brick->checkCollision(_ball);
		}
		else {
			collide = (*iter)->checkCollision(_ball);
		}
		
		++iter;
	}
}

/*
 * renders the collection 
 */
void BrickCollection::renderObject()
{
	render();
}


void BrickCollection::render()
{
	vector<Brick*>::iterator iter 	= _bricks.begin();
	vector<Brick*>::iterator finish = _bricks.end();

	while(iter != finish) {

		//FIXME -- HACK
		if (Brick::BREAKABLE == (*iter)->getType()) {
			// only render if the render flag is set
			BreakableBrick * brick = (BreakableBrick*)(*iter);
			if (! brick->isBroken())
				brick->render();
		}
		else {
			(*iter)->render();
		}
		
		++iter;
	}
}

