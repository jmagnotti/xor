#include "ThetaReader.h"
#include <fstream>
#include <math.h>

void ThetaReader::read(char* filename, vector<double>& thetaVector, int outputUnits)
{
	ifstream in(filename);
	double thetaValue;
	double radiansToDegreesRatio;
	
	if(outputUnits == DEGREES)
	{
		radiansToDegreesRatio = 180.0/M_PI;
	}
	else
		radiansToDegreesRatio = 1.0;

	//alert the user if the file doesn't exist
	if(! in)
	{
		printf("Can't find theta file");
	}
	else
	{		
		while(in)
		{
			//puts the current value from the file into theta value
			in >> thetaValue;
			//convert the radian value if specified and push onto the vector
			thetaVector.push_back(thetaValue*radiansToDegreesRatio);			
		}//end while
	}//end if block
}// end read
