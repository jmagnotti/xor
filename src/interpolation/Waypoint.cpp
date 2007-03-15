#include "Waypoint.h"

namespace XOR {

Waypoint::Waypoint(Orientation * orientation, int interpolationTime, int waitTime, Waypoint * next)
{
	_orientation = orientation;
	//_transition  = transition;
	_waitTime    = waitTime;
	_interpolationTime = interpolationTime;
	_next        = next;
	_target      = NULL;
}

void Waypoint::apply(Transformable *object)
{
	_target = object;
	InterpolationEngine ** interpolators = new InterpolationEngine * [4];
	for (int i = 0; i < 4; i++) {
		interpolators[i] = new TimedInterpolation(_interpolationTime, this);
	}
	//_orientation->setTransformable(object, interpolators);
	//_orientation->incrementTransformable(object, _transition);
	object->setOrientation(_orientation, interpolators);
}

void Waypoint::interpolationComplete()
{
	_ticksRemaining = (int)(_waitTime/(double)Controller::GetInstance(NULL)->getTimer()->getInterval());
	Controller::GetInstance(NULL)->getTimer()->addListener(this);
}

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
		cout << "waiting ... " << _ticksRemaining << " ticks remaining" << endl;
		_ticksRemaining --;
	}
}

}

