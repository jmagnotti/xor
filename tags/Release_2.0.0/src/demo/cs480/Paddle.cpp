#include "Paddle.h"

const float Paddle::SPEED = .4;

Paddle::Paddle(RectangularPrism * rect, int range, Ball * ball)
{
	_rect   = rect;
	_range  = range;
	_ball   = ball;
	_position = rect->getBaseVector();
	cout << _position->toString() << endl;
	_velocity = 0.0;
}

void Paddle::handleKeyEvent(KeyEvent * ke)
{
	if (KeyEvent::KEY_DOWN_EVENT == ke->getType()) {
		if (!_moving) {
			if (SDLK_RIGHT == ke->getKey())
				_velocity  = Paddle::SPEED;
			else if (SDLK_LEFT == ke->getKey())
				_velocity = -1 * Paddle::SPEED;
			_moving = true;
		}
	}
	
	// KeyUpEvent
	else {
		if (_moving && (SDLK_RIGHT == ke->getKey() || 
						SDLK_LEFT  == ke->getKey()) )
			_velocity  = 0.0;
			_moving = false;
	}
}

void Paddle::handlePositionChange(Vector3D * position, int id)
{
	if (_rect->checkCollision(*position + _ball->getMovementVector())) {
		_ball->reverseZVelocity();
		if (_moving)
			_ball->incrementXVelocity(-_velocity/2.0);
	}
}

void Paddle::endFrame()
{
	_position->incrementPosition(Vector3D::X, - _velocity);
	incrementTranslation(new Vector3D(-_velocity, 0, 0));
}

Paddle::~Paddle()
{}

Vector3D * Paddle::getBaseVector()
{
	return _position;
}

Dimension3D * Paddle::getDimension()
{
	return _rect->getDimension();
}

void Paddle::renderObject()
{
	_rect->renderObject();
}


