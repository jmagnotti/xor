#include "BreakableBrick.h"

BreakableBrick::BreakableBrick(Vector3D * position, Dimension3D * size, Paint * paint) :
	Brick(position, size, paint)
{}

BreakableBrick::~BreakableBrick()
{}


void BreakableBrick::doCollide(const int side, Ball * ball)
{
	Brick::doCollide(side, ball);
	_broken = true;
}

bool BreakableBrick::isBroken()
{
	return _broken;
}

const int BreakableBrick::getType()
{
	return Brick::BREAKABLE;
}
