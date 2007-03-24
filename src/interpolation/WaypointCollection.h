#ifndef WAYPOINTCOLLECTION_H
#define WAYPOINTCOLLECTION_H

#include <iostream>
#include <fstream>

#include "Waypoint.h"

using namespace std;

namespace XOR {

/**
 * This class represents a list of Waypoints. Right now it's a very
 * basic implementation since the Waypoint class itself keeps a pointer
 * to the next waypoint, so basically all the collection does is handle
 * the reading from a file.
 */
class WaypointCollection
{
	public:

		/**
		 * Explicit constructor (path of waypoint file)
		 */
		WaypointCollection(const char * path, int interpolationTime, int waitTime);


		/**
		 * Apply initial orientation to an object
		 */
		void initialize(Transformable *object);


		/**
		 * Apply all waypoints to an object
		 */
		void apply(Transformable *object);

	private:

		Orientation * _initial;
		Waypoint *    _firstWaypoint;
};

}

#endif		// WAYPOINTCOLLECTION_H

