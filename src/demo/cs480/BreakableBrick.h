#ifndef BREAKABLEBRICK_H
#define BREAKABLEBRICK_H

#include "Brick.h"

/**
 * A brick object that is "destroyed" when the ball collides with it
 */
class BreakableBrick : public Brick
{
public:
    BreakableBrick(Vector3D * position, Dimension3D * size, Paint * paint);

    ~BreakableBrick();

	bool isBroken();

	/**
	 * returns Brick::BREAKABLE
	 */
	const int getType();

protected:

	void doCollide(const int side, Ball * ball);
	
private:

	RectangularPrism * _brick;
	bool _broken;
};

#endif          // BREAKABLEBRICK_H

