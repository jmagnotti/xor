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
			tmp.push_back((atof(lineBuffer) * 180) / 3.1415926535);
		}
	
		//finished reading the file
		fclose(in);
	}
	
	return tmp;
}

//for reading in two files containing xy values
// TODO change picard generator output to produce single cartesian coord file
// vector<Vector3D*> ThetaReader::readXY(char* xfile, char* yfile)
// {
// 	FILE * xin;
// 	FILE * yin;
// 	
// 	char xBuffer[256];
// 	char yBuffer[256];
// 	
// 	vector<Vector3D*> tmp;
// 	
// 	//open the file for reading
// 	xin = fopen(xfile, "r");
// 	yin = fopen(yfile, "r");
// 	
// 	//if the file doesn't exist, return NULL
// 	if(xin == NULL || yin == NULL)
// 	{
// 		printf("Can't find cartesian coord files");
// 	}
// 	else
// 	{		
// 		while(! feof(xin) && ! feof(yin))
// 		{
// 			//read a line
// 			if(fgets(xBuffer, 256, xin) == NULL && fgets(yBuffer, 256, yin) == NULL)
// 				break; 
// 			//push the coords on the vector	
// 			tmp.push_back(new Vector3D(atof(xBuffer), atof(yBuffer), 0.0f));
// 		}
// 	
// 		//finished reading the file
// 		fclose(xin);
// 		fclose(yin);
// 	}
// 	
// 	return tmp;
// }