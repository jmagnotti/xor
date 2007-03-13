#ifndef WAYPOINT_H
#define WAYPOINT_H

#include "InterpolationEngine.h"
#include "InterpolationListener.h"
#include "TimedInterpolation.h"
#include "../core/Controller.h"
#include "../transform/Orientation.h"
#include "../transform/Transformable.h"
#include "../event/timer/TimerListener.h"

using namespace std;

namespace XOR {

/**
 * This class defines a way-point, which is basically an association
 * between Vector3D locations (+ rotations) and wait times, with
 * an Interpolation transition to the next waypoint.
 */
class Waypoint : public InterpolationListener, public TimerListener
{
	public:

		/**
		 * Explicit constructor
		 */
		Waypoint(Orientation *, int, int, Waypoint *);

		/**
		 * Uses the interpolation to set the orientation, then waits for
		 * the given number of seconds and applies the next waypoint
		 */
		void apply(Transformable *object);

		/**
		 * listen to timer ticks
		 */
		void handleTick();

	private:

		void interpolationComplete();

		Orientation         * _orientation;
		//InterpolationEngine * _transition;
		int                   _interpolationTime;
		int                   _waitTime;
		Waypoint            * _next;
		Transformable		* _target;
		int                   _ticksRemaining;
};

}

#endif		// WAYPOINT_H

