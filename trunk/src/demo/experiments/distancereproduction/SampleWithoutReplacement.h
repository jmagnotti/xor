#ifndef SAMPLEWITHOUTREPLACEMENT_H
#define SAMPLEWITHOUTREPLACEMENT_H

#include <time.h>
#include <stdlib.h>
#include <iostream>

#include <vector>
#include <map>

using namespace std;

/**
 * This project was developed for the Virtual Environment Laboratory at
 * Auburn University.
 *
 * @author John Magnotti (john.magnotti@auburn.edu)
 * @supervisor Jeffrey Katz (katzjf@auburn.edu)
 *
 * @version 1.0
 */
// consider <T> with other data types
class SampleWithoutReplacement
{

public:

	/**
	 * Specify the population to sample from, and the number of times a
	 * number can be repeated. For strict sampling without replacement, set
	 * the number to 1.
	 */
	SampleWithoutReplacement(vector<int> population, int useCount);

	/**
	 *
	 */
	SampleWithoutReplacement(int min, int max, int useCount);

	/**
	 * returns -99 for over-samplings. ENSURE you are not including this in
	 * your dataset. 
	 */
	int sample();

private:

	// can't create a sampler without a population
	SampleWithoutReplacement();

	vector<int> _population;
	map<int, int> _mappings;

	int _maxUse, _maxSamples, _samplesRemaining;
};


#endif			// SAMPLEWITHOUTREPLACEMENT_H

