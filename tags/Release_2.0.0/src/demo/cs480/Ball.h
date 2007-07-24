#ifndef BALL_H
#define BALL_H

#include "../../xor.h"
#include "Sphere.h"

using namespace XOR;

/**
 * The ball is the object the player directs around the gamespace to destroy the bricks.
 * It is contained by the gamespace and reflected off of the bricks and paddle.
 */
class Ball : public Sprite3D
{

public:
	
	/*
	 * Explicit constructor
	 *
	 * @param origin - the current position vector
	 * @param radius - the radius
	 */
    Ball(Vector3D * origin, float radius);
    
	/*
	 * Renders the ball
	 */
    void renderObject();
	

	/*
	 * Returns the ball position
	 *
	 * @return Vector3D*
	 */
	Vector3D * getBaseVector();
	
	/*
	 * Returns the dimensions of the ball in the first
	 * element of the dimension
	 *
	 * @return Dimension3D
	 */
	Dimension3D * getDimension();

	/*
	 * Updates the position of the ball in the
	 * gamespace using the current movement vector
	 */
    void updatePosition(); 

	/**
	 * called on timer.tick
	 */
	void endFrame();

	/**
	 * 
	 */
	void setMovementVector(Vector3D * movement);

	Vector3D * getMovementVector() const;

	/*
	 * quick and easy ways to do reflections of a surface
	 */
	void reverseXVelocity();
	void reverseZVelocity();

	void incrementZVelocity(float amount);
	void incrementXVelocity(float amount);


	void begin();

private:

	Ball();

	Vector3D * _origin;
	Vector3D * _currentPosition;
	Vector3D * _movementVector;

	float _radius;
	Paint * _paint;

	Object3D * _sphere;
	// why write our own sphere class?
	GLUquadric * __sphere;
};

#endif			// BALL_H

