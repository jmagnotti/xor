#ifndef THETAREADER_H
#define THETAREADER_H

#include <vector>

using namespace std;

class ThetaReader
{
public:
	/**
	 * Reads a file of double values with one value per line and
	 * pushes them onto the vector reference from the parameter list.
	 *
	 *@param filename - the file of double values
	 *@param thetaVector - the reference to the vector the values will be pushed onto
	 *@param outputUnits - indicates whether the output will be in degrees or radians
	 *
	 *@author Everette Clemmer
	 */
	static void read(char* filename, vector<double>& thetaVector, int outputUnits);

	/**
	 * Const to be passed as the third parameter to the read function to indicate the
	 * output will be in radians
	 */
	static const int RADIANS = 0;
	
	/**
	 * Const to be passed as the third parameter to the read function to indicate the
	 * output will be in degrees
	 */
	static const int DEGREES = 1;
};
#endif
