#include "Ball.h"


/*
 *  Ball.cpp
 *  CS480FinalProject
 * *  Created by Everette on 4/15/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
Ball::Ball(Vector3D * origin, float radius)
{
	TextureFactory * tf = TextureFactory::GetInstance();
	_paint  = new Paint(tf->createTexture("ball.png"));
	_currentPosition = _origin = origin;

	setTranslation(_currentPosition);
	//_sphere = 
	//	new CompiledObject3D(
	//			new Sphere(origin, radius, 10, 10)
	//			)
	//	;

	_radius = radius;
	//_sphere = gluNewQuadric();

	_movementVector = new Vector3D(0,0,0);
	__sphere = gluNewQuadric();

}

void Ball::updatePosition()
{
	//FIXME have to keep track of the balls position for collisions
	_currentPosition->increment(_movementVector);
	//cout << _currentPosition->toString() << endl;
	setTranslation(_currentPosition);
}

Vector3D * Ball::getBaseVector()
{
	return _currentPosition;
}

Dimension3D * Ball::getDimension()
{
	return new Dimension3D(_radius, 0.0, 0.0);
}

void Ball::renderObject()
{
	glColor3f(0,.6,.9);
	gluSphere(__sphere, .5f, 50,50);
	//_paint->activate();
	//	_sphere->render();
	//_paint->deactivate();
}

void Ball::endFrame()
{
	updatePosition();
}

void Ball::setMovementVector(Vector3D * movement)
{
	_movementVector->clone(movement);
}

void Ball::begin()
{
	Controller::GetInstance()->getTimer()->addListener(this);
}

void Ball::reverseXVelocity()
{
	_movementVector->setPosition(0, _movementVector->getX() * -1);
}

void Ball::reverseZVelocity()
{
	_movementVector->setPosition(2, _movementVector->getZ() * -1);
}

void Ball::incrementXVelocity(float amount)
{
	_movementVector->setPosition(0, _movementVector->getX() + amount);
	// check values
}


void Ball::incrementZVelocity(float amount)
{
	_movementVector->setPosition(2, _movementVector->getZ() + amount);
	// check values
}


Vector3D * Ball::getMovementVector() const
{
	return _movementVector;
}

