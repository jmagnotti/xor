#include "InterpolationManager.h"

InterpolationManager::InterpolationManager(InterpolationListener * photoalbum)
{
	_photoalbum = photoalbum;
	threeHundred = new TimedInterpolation(300, _photoalbum);
}

// this constructor will generate the proper number
// of interpolations for the magnotti transform
InterpolationManager::InterpolationManager(InterpolationListener * photoalbum, int numOfPics)
{
	_photoalbum = photoalbum;
	threeHundred = new TimedInterpolation(300, _photoalbum);

	for(int i = 1; i <= numOfPics; i++)
	{
		interpolations.push_back(new TimedInterpolation(600 * i, _photoalbum));	
	}
}

//~InterpolationManager();
	
/**
 *	getInterpolation(int index) will return the interpolation at
 *	the specified index in the vector.  If the index does not 
 *	exist, NULL is returned.
 *
 *  //TODO: check for existence
 */
TimedInterpolation * InterpolationManager::getInterpolation(int index)
{			
	return interpolations[index];
}
/**
 * getInterpolation(int time, bool search) searches the 
 * vector for a timed interpolation of the same interval
 */
TimedInterpolation * InterpolationManager::getInterpolation(int time, bool search)
{
	vector<TimedInterpolation*>::iterator iter = interpolations.begin();
	vector<TimedInterpolation*>::iterator end  = interpolations.end();
	int i = 0;	
	while (iter != end) 
	{
		++i;
		//TODO: does getTime exist? write it!
		//if((*iter)->getTime() == time)

		++iter;
	}
	return NULL;
}

/**
 * getThreeHundred() returns a 300ms timed interpolation
 * becase it is used so frequently 
 */
TimedInterpolation * InterpolationManager::getThreeHundred()
{
	return threeHundred;
}






