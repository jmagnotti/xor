#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H

#include "../../xor.h"
#include "Picture.h"
#include <vector>

using namespace XOR;
using namespace std;

class PhotoGlass;
class Picture;

class Arrangement
{
public:
	virtual void arrange(vector<Picture*> pictures);
};

class WingArrangement : public Arrangement
{
	public:
		WingArrangement(Picture * highlight); 
		virtual void arrange(vector<Picture*> pictures);
	private:
		Picture * _highlight;  // picture to highlight
		Picture * findNextNorthNeighbor(int, int, Picture* map[5][11]);
		Picture * findNextSouthNeighbor(int, int, Picture* map[5][11]);
		Picture * findNextEastNeighbor(int, int, Picture* map[5][11]);
		Picture * findNextWestNeighbor(int, int, Picture* map[5][11]);
};

class RectangleArrangement : public Arrangement
{
	public:
		RectangleArrangement(Picture * highlight, int width, int height);
		virtual void arrange(vector<Picture*> pictures);
		
		static const float GAP = 0.4f;
		static const float YOFF = 0.0f;
		static const float XOFF = -1.0f;
	private:
		Picture * _highlight;	
		int width;
		int height;
		Picture *** map;
		
		void setNeighbors(int x, int y);
		Picture * findNorthNeighbor(int x, int y);
		Picture * findSouthNeighbor(int x, int y);
		Picture * findEastNeighbor(int x, int y);
		Picture * findWestNeighbor(int x, int y);

};

#endif			// ARRANGEMENT_H
