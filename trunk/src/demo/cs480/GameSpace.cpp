#include "GameSpace.h"

GameSpace::GameSpace(Dimension3D * dimension, Ball * ball) :
    RectangularPrism(new Vector3D(-5,0,0), dimension, new Paint(Color::YELLOW, Paint::HEIGHT_BASED))
{
    removeFace(RectangularPrism::TOP);
	_ball = ball;
}

void GameSpace::handlePositionChange(Vector3D * position, int id)
{
	// ball is trying to leave!
	if (! RectangularPrism::checkCollision(position))	{

		//cout << "BALL LEAVING" << endl;
		
		Vector3D * base = getBaseVector();

		Vector3D * ballLastPos = 
			(*(_ball->getBaseVector())) + _ball->getMovementVector();
		
		if (ballLastPos->getX() < base->getX() || 
				ballLastPos->getX() > base->getX() + getDimension()->getWidth() )
			_ball->reverseXVelocity();
		else  
			_ball->reverseZVelocity();
	}
}


