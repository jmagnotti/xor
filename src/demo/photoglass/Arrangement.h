#ifndef ARRANGEMENT_H
#define ARRANGEMENT_H

#include "../../xor.h"
#include "Picture.h"
#include <vector>

using namespace XOR;
using namespace std;

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

#endif			// ARRANGEMENT_H
