#ifndef PICTURE_H
#define PICTURE_H

#include "../../xor.h"

using namespace XOR;


class Picture 
{
public:

	Picture(Transformable3D * picture);	

	void setNorth(Picture * picture);
	void setSouth(Picture * picture);
	void setEast(Picture * picture);
	void setWest(Picture * picture);

	Picture * getNorth();
	Picture * getSouth();
	Picture * getEast();
	Picture * getWest();

	Transformable3D * getTransformable(); 
	
private:
	Transformable3D * _cube;
	// conceptual position, in relation to 
	// the other pictures
	int cPosition[2]; // x y

	// actual position
	Vector3D * position;

	Picture * _north;
	Picture * _south;
	Picture * _east;
	Picture * _west;	
};


#endif			// ARRANGEMENT_H
