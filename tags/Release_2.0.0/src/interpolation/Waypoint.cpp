#include "Waypoint.h"

namespace XOR {

#if 0
Waypoint::Waypoint(Orientation * orientation, int interpolationTime, int waitTime, Waypoint * next)
{
	interpolators = new InterpolationEngine * [4];
	for (int i = 0; i < 4; i++) {
		interpolators[i] = NULL;
	}
	_orientation = orientation;
	_waitTime    = waitTime;
	_interpolationTime = interpolationTime;
	_next        = next;
	_target      = NULL;
	_id          = 0;
}

Waypoint::Waypoint(Orientation * orientation, int interpolationTime, int waitTime, Waypoint * next, int id)
{
	interpolators = new InterpolationEngine * [4];
	for (int i = 0; i < 4; i++) {
		interpolators[i] = NULL;
	}
	_orientation = orientation;
	_waitTime    = waitTime;
	_interpolationTime = interpolationTime;
	_next        = next;
	_target      = NULL;
	_id			 = id;
}


/*
 * get "next" pointer
 */
Waypoint * Waypoint::getNext()
{
	return _next;
}

/*
 * set "next" pointer
 */
void Waypoint::setNext(Waypoint * next)
{
	_next = next;
}

/*
 * get a reference to the orientation
 */
Orientation * Waypoint::getOrientation()
{
	return _orientation;
}

/*
 * increment the waypoint
 */
void Waypoint::apply(Transformable *object)
{
	//if (object == NULL)
		//cout << "it's null!" << endl;
	//else
		//cout << "applying waypoint #" << _id << ": " << this << endl;

	_target = object;
	//cout << "creating interpolators..." << endl;
	for (int i = 0; i < 4; i++) {
		//cout << "    interpolator #" << i << endl;
		if (interpolators[i] != NULL) {
			//cout << "deleting interpolator #" << i << endl;
			delete interpolators[i];
		}
		if (i == 0)
			interpolators[i] = new TimedInterpolation(_interpolationTime, this);
		else
			interpolators[i] = new TimedInterpolation(_interpolationTime);
	}
	//cout << _orientation->getRotation(Orientation::THETA) << endl;
	//cout << "interpolators created" << endl;
	//object->setOrientation(_orientation, interpolators);
	object->incrementOrientation(_orientation, interpolators);
}

/*
 * set the waypoint using null interpolations
 */
void Waypoint::applyImmediately(Transformable *object)
{
	_target = object;
	object->setOrientation(_orientation); 
}

/*
 * the interpolation is done, start waiting
 */
void Waypoint::interpolationComplete()
{
	//cout << " waypoint #" << _id << " done!" << endl;
	_ticksRemaining = (int)(_waitTime/(double)Controller::GetInstance(NULL)->getTimer()->getInterval());
	Controller::GetInstance(NULL)->getTimer()->addListener(this);
}

/*
 * done waiting, start next waypoint
 */
void Waypoint::handleTick()
{
	if (_ticksRemaining <= 0) {
		if (_next != NULL && _target != NULL) {
			_next->apply(_target);
			_target = NULL;
			Controller::GetInstance(NULL)->getTimer()->removeListener(this);
		}
	}
	else {
		//cout << "waiting ... " << _ticksRemaining << " ticks remaining" << endl;
		_ticksRemaining --;
	}
}

/*
 * print waypoint debug info
 */
void Waypoint::print()
{
	cout << "waypoint #" << _id << "  addr: " << this << "  next " << _next << endl;
}

#endif
}

