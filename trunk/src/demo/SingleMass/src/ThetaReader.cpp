#include "ThetaReader.h"

vector<float> ThetaReader::read(char* filename)
{
	FILE * in;
	char lineBuffer[256];
	vector<float> tmp;
	
	//open the file for reading
	in = fopen(filename, "r");
	
	//if the file doesn't exist, return NULL
	if(in == NULL)
	{
		printf("Can't find theta file");
		fflush(in);
	}
	else
	{		
		while(! feof(in))
		{
			//read a line
			if(fgets(lineBuffer, 256, in) == NULL)
				break; 
				
			tmp.push_back(atof(lineBuffer));
		}
	
		//finished reading the file
		fclose(in);
	}
	
	return tmp;
}