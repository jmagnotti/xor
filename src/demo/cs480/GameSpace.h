#ifndef GAMESPACE_H
#define GAMESPACE_H


#include "../../xor.h"
#include <vector>
#include "Ball.h"
#include "Brick.h"


/**
 *
 */
class GameSpace : public RectangularPrism, public Sprite3DListener
{

public:

	GameSpace(Dimension3D * dimension, Ball * ball);

	/**
	 * called when the ball moves
	 */
	void handlePositionChange(Vector3D * position, int id);

private:

	Ball * _ball;

};

#endif			// GAMESPACE_H

