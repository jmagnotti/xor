#include "Arrangement.h"
#include "PhotoGlass.h"
#include <iostream>

using namespace XOR;
using namespace std;
void Arrangement::arrange(vector<Picture*> pictures) 
{
}

void WingArrangement::arrange(vector<Picture*> pictures) 
{
	cout << "in arrange()" << endl;
	// width height of wall
	const int HEIGHT = 5;
	const int WIDTH  = 11;
	const float GAP = 0.5f; // space between pics
	const float YOFF = 0.0f; // shifts the pics up to the top
	const float XOFF = -1.0f;
	// priority map
	// what should be filled first
	int priomap[HEIGHT][WIDTH] = {
		{0,0,0,1,1,1,1,1,0,0,0},
		{2,2,2,1,1,1,1,1,3,3,3},
		{2,2,2,1,1,1,1,1,3,3,3},
		{2,2,2,1,1,1,1,1,3,3,3},
		{0,0,0,1,1,1,1,1,0,0,0}
	};

	Picture * map[HEIGHT][WIDTH];
	// zero map
	for(int ii = 0; ii < HEIGHT; ii++)
		for(int jj = 0;  jj < WIDTH; jj++)
			map[ii][jj] = NULL;

	int matches = 0;
	int maxmatch = pictures.size();

	cout << "Copying pointers in arrange()" << endl;
	for(int ii = 0; ii < HEIGHT && matches < maxmatch; ii++) {
		for(int jj = 0; jj < WIDTH && matches < maxmatch; jj++) { 
			if(priomap[ii][jj] == 1) {
				cout << "Setting map[" << ii << "][" << jj << "]" << endl;
				map[ii][jj] = pictures[matches++];
			}
		}
	}

	for(int ii = 0; ii < HEIGHT && matches < maxmatch; ii++) {
		for(int jj = 0; jj < WIDTH && matches < maxmatch; jj++) { 
			if(priomap[ii][jj] == 2) {
				cout << "Setting map[" << ii << "][" << jj << "]" << endl;
				map[ii][jj] = pictures[matches++];
			}
		}
	}
	
	for(int ii = 0; ii < HEIGHT && matches < maxmatch; ii++) {
		for(int jj = 0; jj < WIDTH && matches < maxmatch; jj++) { 
			if(priomap[ii][jj] == 3){
				cout << "Setting map[" << ii << "][" << jj << "]" << endl;
				map[ii][jj] = pictures[matches++];
			}
		}
	}
	cout << "Building qll in arrange()" << endl;
	// now build the quad linked list
	for(int ii = 0; ii < HEIGHT; ii++) {
		for(int jj = 0; jj < WIDTH; jj++) { 
			if(map[ii][jj] != NULL) {
				cout << "Setting neighbors for " << ii << ", " << jj << endl;
				map[ii][jj]->setNorth(findNextNorthNeighbor(ii,jj,map));
				map[ii][jj]->setSouth(findNextSouthNeighbor(ii,jj,map));
				map[ii][jj]->setEast(findNextEastNeighbor(ii,jj,map));
				map[ii][jj]->setWest(findNextWestNeighbor(ii,jj,map));
			}
		}
	}
	cout << "Attempting to translate in arrange()" << endl;
	// now move the pictures into a meaningful spot
	for(int ii = 0; ii < HEIGHT; ii++) {
		for(int jj = 0; jj < WIDTH; jj++) {
			if(map[ii][jj] != NULL) {
				cout << "Creating MoveAction for " << ii << "," << jj << "." << endl;
								
				// To place all of our cubes we'll need to do some dirty
				// work.  Since the center of the 5x5 corresponds to
				// array index [6][2] we'll subtract that from ii/jj
				// so it stays in the center
				map[ii][jj]->setDefaultPosition(
							new Vector3D((jj- 6) + (jj - 6) * GAP + XOFF, // x
								(ii - 2)+ (ii - 2) * GAP + YOFF,	    // y
								-9));                               //z
				map[ii][jj]->goToDefault(3000);
			}
		}
	}
	
}

Picture * WingArrangement::findNextNorthNeighbor(int ii, int jj, Picture * map[5][11])
{
	if(map[ii][jj] != NULL)
	{
		int curRow = ii;
		bool found = false; // have we found a neighbor
		// we'll check up to 5 rows north of the current 
		// index (ii)
		for(int i = 1; i < 5 && !found; i++) 
		{
			// if we've reached the top, loop to bottom
			if(--curRow < 0)
				curRow = 4;	
			if(map[curRow][jj] != NULL) {
				found = true;
				return map[curRow][jj];
			}
		}
	}

	// if we had no luck just return pointer to self
	return map[ii][jj];
}

Picture * WingArrangement::findNextSouthNeighbor(int ii, int jj, Picture * map[5][11])
{
	if(map[ii][jj] != NULL)
	{
		int curRow = ii;
		bool found = false; // have we found a neighbor
		// we'll check up to 5 rows south of the current 
		// index (ii)
		for(int i = 1; i < 5 && !found; i++) 
		{
			// if we've reached the top, loop to top
			if(++curRow > 4)
				curRow = 0;	
			if(map[curRow][jj] != NULL) {
				found = true;
				return map[curRow][jj];
			}
		}
	}

	// if we had no luck just return pointer to self
	return map[ii][jj];
}

Picture * WingArrangement::findNextEastNeighbor(int ii, int jj, Picture * map[5][11])
{
	if(map[ii][jj] != NULL)
	{
		int curCol = jj;
		bool found = false; // have we found a neighbor
		// we'll check up to 11 cols east of the current 
		// index (jj)
		for(int i = 1; i < 11 && !found; i++) 
		{
			// if we've reached the top, loop to left
			if(++curCol > 11)
				curCol = 0;	
			if(map[ii][curCol] != NULL) {
				found = true;
				return map[ii][curCol];
			}
		}
	}

	// if we had no luck just return pointer to self
	return map[ii][jj];
}

Picture * WingArrangement::findNextWestNeighbor(int ii, int jj, Picture * map[5][11])
{
	if(map[ii][jj] != NULL)
	{
		int curCol = jj;
		bool found = false; // have we found a neighbor
		// we'll check up to 11 cols east of the current 
		// index (jj)
		for(int i = 1; i < 11 && !found; i++) 
		{
			// if we've reached the top, loop to left
			if(--curCol < 0)
				curCol = 10;	
			if(map[ii][curCol] != NULL) {
				found = true;
				return map[ii][curCol];
			}
		}
	}

	// if we had no luck just return pointer to self
	return map[ii][jj];
}
