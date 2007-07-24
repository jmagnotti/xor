#ifndef PADDLE_H
#define PADDLE_H

#include "../../xor.h"
#include "Brick.h"
#include "Ball.h"

using namespace XOR;

class Paddle : public Sprite3D, public KeyboardListener, public Sprite3DListener
{

public:

	static const float SPEED;
	
	/*
	 * Explicit constructor 
	 * decorate a RectPrism
	 */
	Paddle(RectangularPrism * rect, int range, Ball * ball);


	/*
	 * Destructor
	 */
	virtual ~Paddle();

	
	/*
	 * Returns the origin vector of the paddle
	 *
	 * @return Vector3D
	 */
	Vector3D * getBaseVector();

	
	/*
	 * Returns the dimensions of the paddle
	 *
	 * @return Dimension3D
	 */
	Dimension3D * getDimension();


	/**
	 * handles key presses to move the paddle around
	 */
	void handleKeyEvent(KeyEvent * ke);

	
	/*
	 * Calls Rectangular Prism's render method to render
	 * the paddle
	 */
	void renderObject();


	/**
	 * called when the ball moves
	 */
	void handlePositionChange(Vector3D * position, int id);


	/**
	 * updates the position of the paddle
	 */
	void endFrame();


private:

	Paddle();

	Ball * _ball;
	RectangularPrism * _rect;

	int _range;
	bool _moving;


	Vector3D * _position;
	float _velocity;
};

#endif //PADDLE_H

