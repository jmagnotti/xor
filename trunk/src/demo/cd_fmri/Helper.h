#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <iostream>
#include "Trial.h"

using namespace std;

class Helper {

public:

	/**
	 * Inplace reorder of a. Equivalent to SampleWOReplacement(pop, pop, pop.size());
	 */
	static void Reorder(vector<int> * a);

	static void Reorder(vector<Trial*> * a);

	/**
	 * Passing in a seed allows us to randomize two vectors in the same way.
	 * Useful for matched trials. Just sets the seed and calls Reorder(a);
	 */
	static void Reorder(vector<Trial*> * a, int seed);

    /**
     * Returns the [position % a.size] + 1 item from the vector with wrapping
     */
	static int Rot_1(vector<int> a, int position);

	/**
	 * Provide haystack and the needle. Returns position or -1
	 */
	static int FindInVec(vector<int>,  int);

	static void PrintVector(vector<int>);

	/**
	 * Calculates a sample of size n from pop into sample. 
	 *
	 * Input Condition: [pop.size() >= n]
	 */
	static void SampleWOReplacement(vector<int> pop, vector<int> * sample, int n);

    /**
     * Allows nRepeats number of duplicates in obtaining the n samples
    */
	static void SampleWithLimitedReplacement(vector<int> pop, vector<int> * sample, int nRepeats, int n);

	/**
	 * Calculates a sample of size n ensuring that each sample[i] is not found in stale
	 * There's probably a faster way to do this...
	 *
	 * Input Condition: [pop.size() - stale.size() >= n]
	 */
	static void FreshSampleWOReplacement(vector<int> pop, vector<int> * sample, vector<int> stale, int n);

	/**
	 * Singleton seed function
	 */
	static void SeedGenerator();

    /**
     * Generate 0, 1 result
     */
    static int flipCoin();

private:
	static bool _seeded;

};

#endif			// HELPER_H
