#ifndef THETAREADER_H
#define THETAREADER_H

#include <vector>

using namespace std;

class ThetaReader
{
public:
	/**
	 * Static method reads float values for theta, one per line,
	 * from the input file and returns them as a vector
	 */
	static vector<double> read(char* filename);
};
#endif
