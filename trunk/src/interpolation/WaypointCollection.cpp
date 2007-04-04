#include "WaypointCollection.h"

namespace XOR {

WaypointCollection::WaypointCollection(const char * path, int interpolationTime, int waitTime, bool loop)
{
	float x,y,z,t,p,r;
	float cx,cy,cz,ct,cp,cr;
	Waypoint * previous = NULL;
	Waypoint * current = NULL;
	Orientation * temp;
	int count = 0;

	fstream points(path);

	if (!points) {
		cout << "Error opening file: " << path << endl;
		_first = new Waypoint(new Orientation(), 0, 0, NULL);
		_last  = new Waypoint(new Orientation(), 0, 0, NULL);
		return;
	}

	while (points >> x && points >> y && points >> z &&
		   points >> t && points >> p && points >> r) {
		count ++;
		temp = new Orientation(new Translate(x, y, z), 
								   new Rotate(r,0,0,1), 
								   new Rotate(p,1,0,0),
								   new Rotate(t,0,1,0));
		//cout << endl << "next orientation:" << endl;
		//temp->print();
		//current = new Waypoint(temp, interpolationTime, waitTime, NULL);
		if (count == 1) {
			_initial = temp;
			cx=x;cy=y;cz=z;ct=t;cp=p;cr=r;
			//printf("I  : %10.4f  %10.4f  %10.4f  %10.4f  %10.4f  %10.4f\n",
					//x,y,z,t,p,r);
		} else {
			// increment current orientation
			cx+=x;cy+=y;cz+=z;ct+=t;cp+=p;cr+=r;
			//printf("inc: %10.4f  %10.4f  %10.4f  %10.4f  %10.4f  %10.4f\n",
					//x,y,z,t,p,r);
			//printf("cur: %10.4f  %10.4f  %10.4f  %10.4f  %10.4f  %10.4f\n",
					//cx,cy,cz,ct,cp,cr);
			current = new Waypoint(temp, interpolationTime, waitTime, NULL, count);
			if (previous != NULL)
				previous->setNext(current);
			if (count == 2)
				_first = current;
			previous = current;
		}
	}
	if (current != NULL) {
		_last = current;
	}

	// set up loop
	if (loop && _last != NULL) {
		_last->setNext(_first);

		// get initial orientation
		Vector3D * ipt = _initial->getTranslation();
		float ipat = _initial->getRotation(Orientation::THETA),
			  ipap = _initial->getRotation(Orientation::PHI),
			  ipar = _initial->getRotation(Orientation::ROLL);
		ipat = GraphicsConversionUtility::GetInstance()->floatModulus(ipat, 360);
		ipap = GraphicsConversionUtility::GetInstance()->floatModulus(ipap, 360);
		ipar = GraphicsConversionUtility::GetInstance()->floatModulus(ipar, 360);

		// current orientation (incrementally calculated from above)
		ct = GraphicsConversionUtility::GetInstance()->floatModulus(ct, 360);
		cp = GraphicsConversionUtility::GetInstance()->floatModulus(cp, 360);
		cr = GraphicsConversionUtility::GetInstance()->floatModulus(cr, 360);

		// new orientation that increments from final orientation in
		// file back to the initial orientation (which was NOT given as
		// an increment in the file!)
		temp = new Orientation(new Translate(ipt->getX() - cx,
					                         ipt->getY() - cy,
											 ipt->getZ() - cz),
				               new Rotate(ipar-cr, 0,0,1),
							   new Rotate(ipap-cp, 1,0,0),
							   new Rotate(ipat-ct, 0,1,0));

		//printf("II : %10.4f  %10.4f  %10.4f  %10.4f  %10.4f  %10.4f\n",
				//ipt->getX(),ipt->getY(),ipt->getZ(), ipat,ipap,ipar);
		//Vector3D * iptt = temp->getTranslation();
		//printf("new: %10.4f  %10.4f  %10.4f  %10.4f  %10.4f  %10.4f\n",
				//iptt->getX(),iptt->getY(),iptt->getZ(),
				//temp->getRotation(Orientation::THETA),
				//temp->getRotation(Orientation::PHI),
				//temp->getRotation(Orientation::ROLL));
		//delete iptt;

		current = new Waypoint(temp, interpolationTime, waitTime, NULL, 1);
		_last->setNext(current);
		current->setNext(_first);
		_last = current;

		// temporary vector pointer
		delete ipt;
	}
}


void WaypointCollection::initialize(Transformable * object)
{
	//_first->applyImmediately(object);
	object->setOrientation(_initial);
}


void WaypointCollection::apply(Transformable * object)
{
	_first->apply(object);
}


void WaypointCollection::print()
{
	Waypoint *next = _first;
	cout << endl;
	cout << "** COLLECTION -- FIRST WAYPOINT:" << endl;
	while (next != NULL && next != _last) {
		next->print();
		next = next->getNext();
	}
	if (next != NULL) {
		cout << "** COLLECTION -- LAST WAYPOINT:" << endl;
		next->print();
	}
	cout << endl;
}

}

