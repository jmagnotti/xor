#include "ThetaReader.h"

void ThetaReader::read(char* filename, vector<float> thetas)
{
	FILE * in;
	char lineBuffer[256];
	
	//open the file for reading
	in = fopen(filename, "r");
	
	//if the file doesn't exist, return NULL
	if(in == NULL)
	{
		printf("Can't find init file");
		fflush(in);
	}
	else
	{		
		while(! feof(in))
		{
			//read a line
			if(fgets(lineBuffer, 256, in) == NULL)
				break; 
				
			thetas.push_back(atof(lineBuffer));
		}
	
		//finished reading the file
		fclose(in);
	}
	
}