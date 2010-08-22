#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <iostream>

using namespace std;

class Helper {

public:

	/**
	 * Inplace reorder of a. Equivalent to SampleWOReplacement(pop, pop, pop.size());
	 */
	static void Reorder(vector<int> * a);

	/**
	 * Calculates a sample of size n from pop into sample. 
	 *
	 * Input Condition: [pop.size() >= n]
	 */
	static void SampleWOReplacement(vector<int> pop, vector<int> * sample, int n);

	/**
	 * Calculates a sample of size n ensuring that each sample[i] is not found in state
	 *
	 * Input Condition: [pop.size() - stale.size() >= n]
	 */
	static void FreshSampleWOReplacement(vector<int> pop, vector<int> * sample, vector<int> stale, int n);

};

#endif			// HELPER_H
