#include "Brick.h"

/*
 * invoke the super ctor
 */
Brick::Brick(Vector3D * position, Dimension3D * size,
		Paint * paint) :
	RectangularPrism(position, size, paint)
{}

Brick::~Brick()
{}

/*
 * add listener
 */
void Brick::addListener(HitListener *hl)
{
	_listeners.push_back(hl);
}


/*
 * rem listener 
 */
void Brick::removeListener(HitListener *hl)
{
    bool removed = false;

    list<HitListener*>::iterator iter   = _listeners.begin();
    list<HitListener*>::iterator finish = _listeners.end();

    while (!removed && iter != finish) {
        if (*iter == hl) {
            _listeners.erase(iter);
            removed = true;
		}
		else { ++iter; }
    }
}


/*
 * notify, not affected by list removals
 */
void Brick::notifyListeners()
{
    list<HitListener*>::iterator iter   = _listeners.begin();
	list<HitListener*>::iterator next   = _listeners.begin();
    list<HitListener*>::iterator finish = _listeners.end();

    while (iter != finish) {
		++next;
		(*iter)->handleHit(this);
        iter = next;
    }

}

bool Brick::checkCollision(Ball * ball)
{
	if (RectangularPrism::checkCollision(ball->getBaseVector())) {
		Vector3D * base = getBaseVector();

		Vector3D * ballLastPos = 
			(*(ball->getBaseVector())) - ball->getMovementVector();
		
		if (ballLastPos->getX() < base->getX() || 
				ballLastPos->getX() > base->getX() + getDimension()->getWidth() )
			doCollide(RectangularPrism::LEFT, ball);
		else 
			doCollide(RectangularPrism::FRONT, ball);

		return true;
	}

	return false;
}

/*
 * default collision
 */
void Brick::doCollide(const int side, Ball * ball)
{
	// change the balls motion
	if (side == RectangularPrism::LEFT || side == RectangularPrism::RIGHT) 
		ball->reverseXVelocity();
	else  
		ball->reverseZVelocity();
	
	// tell the world
	notifyListeners();
}
