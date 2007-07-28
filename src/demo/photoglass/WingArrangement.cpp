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
	// width height of wall
	const int HEIGHT = 5;
	const int WIDTH  = 11;
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

	int searchrow = 0;
	int searchcol = 0;
	
	// here's our super sweet 
	// sloppily written way of generating 
	// an array of pointers so we can
	// build a quad linked list
	for(int i = 0; i < pictures.size(); i++) {
		
		bool match = false;
		for(int ii = searchrow; ii < HEIGHT && !match; ii++) {
			for(int jj = searchcol; jj <  WIDTH && !match; jj++) {
				if(priomap[ii][jj] == 1) {
					map[ii][jj] = pictures[i];
					searchrow = ii;
					searchcol = jj;
					match = true;
				}
			}
		}
	}

	// now build the quad linked list
	for(int ii = 0; ii < HEIGHT; ii++) {
		for(int jj = 0; jj < WIDTH; jj++) { 
			if(map[ii][jj] != NULL) {
				map[ii][jj]->setNorth(findNextNorthNeighbor(ii,jj,map));
				map[ii][jj]->setSouth(findNextSouthNeighbor(ii,jj,map));
				map[ii][jj]->setEast(findNextEastNeighbor(ii,jj,map));
				map[ii][jj]->setWest(findNextWestNeighbor(ii,jj,map));
			}
		}
	}
	// now move the pictures into a meaningful spot
	for(int ii = 0; ii < HEIGHT; ii++) {
		for(int jj = 0; jj < WIDTH; jj++) {
			cout << "Creating MoveAction for " << ii << "," << jj << "." << endl;
			new MoveAction(map[ii][jj]->getTransformable(), new Vector3D(ii - 2, jj - 6, -1), NULL);
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
