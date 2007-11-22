#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>

#ifndef __APPLE__
 #include <windows.h>
#endif

#include "../../sva/sva.h" // Must be after windows.h

#ifdef __APPLE__
 #include <OpenGL/gl.h>
#else
 #include "GL/gl.h"
#endif

#define PI 3.1415926535

#include "GLPendulum.h"

using namespace std;
/**
 * A digital double pendulum model
 *
 * @author Everette Clemmer
 * @version 1.0
 *
 * Based on 'p2-project*.c'
 * @author Seth Fowler
 * @version 1.0
 */


// Global Variables
//
// Note: Many variables must be global because the display()
// callback doesn't (and can't easily) have parameters
//
float currentTime;
float *x;
float *y;
float *t;
float deltat, tFirst, tLast;
int   currentIndex;
int   steps;                  // Number of times in [tFirst, tLast)
const float LENGTH_ADVANCE = 0.5f;


vector<float> thetas;
int thetaCounter = 0;

GLPendulum * glPendulum;

// Material / Lighting Data for OpenGL
GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat softWhite[] = {0.05f, 0.035f, 0.025f};
GLfloat lightPos[] = {1.0f, 0.0f, 2.0f, 1.0f};


// // Empty Functions Required by the SVA Library
// //
// void onMouseClick(int button, int state, GLfloat x, GLfloat y){}
// void onMouseDrag(GLfloat x, GLfloat y){}
// void onMouseMove(GLfloat x, GLfloat y){}

/**
 * Reads in the theta values from a file and stores them in the
 * vector thetas
 */
void init(char * filename)
{
	FILE * in;
	char lineBuffer[256];
	
	//open the file for reading
	in = fopen(filename, "r");
	
	//if the file is empty, return NULL
	if(in == NULL)
	{
		printf("Empty init file");
		fclose(in);
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

// /**
//  * The timer callback
//  *
//  * @param value  The current elapsed animation time (in milliseconds)
//  */
// void onTimer(int value)
// {
//   	if(thetaCounter >= thetas.size())
// 	{
// 		thetaCounter = 0;
// 	}
// 
// 	else
// 		thetaCounter++;
// }
// 
// 
// /**
//  * The display callback
//  */
// void onDisplay()
// {
// 	char label[80];
// 
// 	glPendulum->setDrawnLength(1.0f);
// 	glPendulum->draw(thetas[thetaCounter]);
// }

/**
 * The entry point of the application.
 *
 * @param argc  The number of command line arguments
 * @param argv  The array of command line arguments
 * @return      A status code
 */
int main(int argc, char **argv)
{
	// float animationLength, delayPerStep;
	// float min[3], max[3];

	// // Default animation parameters
	// 	tFirst = 0.0;
	// 	tLast = 6.28;   
	// 	steps  = 1000;
	// 
	// 	deltat = (tLast - tFirst) / (float)steps;

	// x = new float[steps+1];
	// 	y = new float[steps+1];
	// 	t = new float[steps+1];

	// Default mins, maxes
	// min[0] = min[1] = min[2] = -5.0;
	// max[0] = max[1] = max[2] = 5.0;
	// 
	// svaCreate(argc, argv, min, max);
	// svaSetAxesLabels("x", "y", "z");
	// svaSetRotation(0.0, 0.0, 0.0);
	// 
	// animationLength = 10.0; // shortest possible length in seconds
	// delayPerStep    = animationLength / (float)steps;
	// 
	// currentIndex    = -1;
	// currentTime     = -deltat; 

	// Enable OpenGL stuff
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, softWhite);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// Create the GLPendulum object used for rendering the pendulum
	glPendulum = new GLPendulum(1.0f);
	glPendulum->setArrowsEnabled(true);
	
	init(argv[1]);

	//svaStartAnimation((int)(delayPerStep*1000.));  // in milliseconds
}