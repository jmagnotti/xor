#include "ThetaReader.h"

//for reading in theta values from a file
vector<double> ThetaReader::read(char* filename)
{
	FILE * in;
	char lineBuffer[256];
	vector<double> tmp;
	
	//open the file for reading
	in = fopen(filename, "r");
	
	//if the file doesn't exist, return NULL
	if(in == NULL)
	{
		printf("Can't find theta file");
	}
	else
	{		
		while(! feof(in))
		{
			//read a line
			if(fgets(lineBuffer, 256, in) == NULL)
				break; 
			//push the value onto the vector
			//thetafile is in rads so need to convert to deg	
			tmp.push_back((atof(lineBuffer) * 180) / 3.1415926535);
			printf("%f", (atof(lineBuffer) * 180) / 3.1415926535);
		}
	
		//finished reading the file
		fclose(in);
	}
	
	return tmp;
}
