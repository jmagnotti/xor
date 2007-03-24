#include "WaypointCollection.h"

namespace XOR {

WaypointCollection::WaypointCollection(const char * path, int interpolationTime, int waitTime)
{
	float x,y,z,t,p,r;
	Waypoint * previous = NULL;
	Waypoint * current = NULL;
	Orientation * temp;
	int count = 0;

	fstream points(path);

	if (!points) {
		cout << "Error opening file: " << path << endl;
		_initial = new Orientation();
		_firstWaypoint = new Waypoint(_initial, 0, 0, NULL);
		return;
	}

	while (points >> x && points >> y && points >> z &&
		   points >> t && points >> p && points >> r) {
		count ++;
		if (count == 1) {
			_initial = new Orientation(new Translate(x, y, z), 
					                   new Rotate(r,0,0,1), 
									   new Rotate(p,1,0,0),
									   new Rotate(t,0,1,0));
			cout << endl << "initial orientation:" << endl;
			_initial->print();
		} else {
			temp = new Orientation(new Translate(x, y, z), 
					                   new Rotate(r,0,0,1), 
									   new Rotate(p,1,0,0),
									   new Rotate(t,0,1,0));
			cout << endl << "next orientation:" << endl;
			temp->print();
			current = new Waypoint(temp, interpolationTime, waitTime, NULL);
			if (previous != NULL)
				previous->setNext(current);
			if (count == 2)
				_firstWaypoint = current;
			previous = current;
		}
	}
}


void WaypointCollection::initialize(Transformable * object)
{
	InterpolationEngine * interpolations[4] = {NULL, NULL, NULL, NULL};
	object->setOrientation(_initial, interpolations);
}


void WaypointCollection::apply(Transformable * object)
{
	_firstWaypoint->apply(object);
}


}

