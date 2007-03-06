#ifndef INTERPOLATIONMANAGER_H
#define INTERPOLATIONMANAGER_H

#include "../../xor.h"
#include <vector>

using namespace XOR;
using namespace std;

class InterpolationManager
{
	public:
		InterpolationManager(InterpolationListener * photoalbum);
		InterpolationManager(InterpolationListener * photoalbum, int numOfPics);

		TimedInterpolation * getInterpolation(int index);
		TimedInterpolation * getInterpolation(int time, bool search);

		TimedInterpolation * getThreeHundred();
	
	private:
		InterpolationListener * _photoalbum;
		vector<TimedInterpolation*> interpolations;
		TimedInterpolation * threeHundred;

};

#endif
