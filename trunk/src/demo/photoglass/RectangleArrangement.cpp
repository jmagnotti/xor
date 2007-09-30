#include "Arrangement.h"
#include "PhotoGlass.h"
#include <iostream>

using namespace XOR;
using namespace std;

/**
 * This simple constructor creates a new arrangement of pictures.
 * If improper values are given for width and height, a value of
 * one is used.
 *
 * @param highlight The picture to be highlighted by default
 * @param width Width in pictures
 * @param height Height in pictures
 */
RectangleArrangement::RectangleArrangement(Picture * highlight, int width, int height)
{
	this->width  = 1;
	this->height = 1;

	if(width > 0)
		this->width = width;
	if(height > 0)
		this->height = height;

	this->map = new Picture**[width];
	for(int i = 0; i < height; i++)
		this->map[i] = new Picture*[height];

	_highlight = highlight;
}
void RectangleArrangement::arrange(vector<Picture*> pictures)
{
	// populate the map 
	int alloted = 0;  // how many pictures we've used
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			if(alloted < pictures.size())
				map[i][j] = pictures[alloted++];
			else
				map[i][j] = NULL;
		}
	}

	// convert map to a qll
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			if(map[i][j] != NULL)
					setNeighbors(i, j);
		}
	}
	for(int ii = 0; ii < width; ii++) {
		for(int jj = 0; jj < height; jj++) {
			if(map[ii][jj] != NULL) {
				cout << "Creating MoveAction for " << ii << "," << jj << "." << endl;
								
				// To place all of our cubes we'll need to do some dirty
				// work.  Since the center of the 5x5 corresponds to
				// array index [6][2] we'll subtract that from ii/jj
				// so it stays in the center
				map[ii][jj]->setDefaultPosition(
							new Vector3D((jj- 6) + (jj - 6) * GAP + XOFF, // x
								-1 * ((ii - 2)+ (ii - 2) * GAP) + YOFF,	    // y
								-9));                               //z
				if(map[ii][jj] == _highlight) 
					_highlight->highlight();
				map[ii][jj]->goToDefault(3000);
			}
		}
	}
	
}

/*
 * finds and sets all of the neighbors for the xth yth element
 * in the map.
 */
void RectangleArrangement::setNeighbors(int x, int y)
{
	Picture * currentPicture = map[x][y];	
	if(currentPicture != NULL)
	{
		// TODO: Something is horribly amiss here!!
		// Everything is wrong with the north south
		// east west mappings...
		map[x][y]->setNorth(findWestNeighbor(x, y));
		map[x][y]->setSouth(findEastNeighbor(x, y));
		map[x][y]->setEast(findSouthNeighbor(x, y));
		map[x][y]->setWest(findNorthNeighbor(x, y));

	}
}

Picture * RectangleArrangement::findNorthNeighbor(int x, int y)
{
	if(map[x][y] != NULL)
	{
		int curRow = y;
		bool found = false; // have we found a neighbor yet?
		for(int i = 1; i < height && !found; i++)
		{
				// loop to bottom if we reached the top
				if(--curRow < 0)
						curRow = height - 1;
				if(map[x][curRow] != NULL)
				{
						found = true;
						return map[x][curRow];
				}
		}

	}	

	// if there was no match return pointer to self
	return map[x][y];
}

Picture * RectangleArrangement::findSouthNeighbor(int x, int y)
{
	if(map[x][y] != NULL)
	{
		int curRow = y;
		bool found = false; // have we found a neighbor yet?
		for(int i = 1; i < height && !found; i++)
		{
				// loop to bottom of we reached the top
				if(++curRow >= height)
						curRow = 0;
				if(map[x][curRow] != NULL)
				{
						found = true;
						return map[x][curRow];
				}
		}
	}	

	// if there was no match return pointer to self
	return map[x][y];
}

Picture * RectangleArrangement::findEastNeighbor(int x, int y)
{
	if(map[x][y] != NULL)
	{
		int curCol = x;
		bool found = false; // have we found a neighbor yet?
		for(int i = 1; i < width && !found; i++)
		{
				// loop to top of we reached the bottom
				if(++curCol >= width)
						curCol = 0;
				if(map[curCol][y] != NULL)
				{
						found = true;
						return map[curCol][y];
				}
		}
	}	

	// if there was no match return pointer to self
	return map[x][y];
}

Picture * RectangleArrangement::findWestNeighbor(int x, int y)
{
	if(map[x][y] != NULL)
	{
		int curCol = x; 
		bool found = false; // have we found a neighbor yet?
		for(int i = 1; i < width && !found; i++)
		{
				// wrap
				if(--curCol < 0)
						curCol = width - 1;
				if(map[curCol][y] != NULL)
				{
						found = true;
						return map[curCol][y];
				}
		}
	}	

	// if there was no match return pointer to self
	return map[x][y];
}
