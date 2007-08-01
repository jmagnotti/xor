#ifndef PICTURE_H
#define PICTURE_H

#include "../../xor.h"

using namespace XOR;


class Picture 
{
public:

	Picture(Transformable3D * picture);	

	void setDefaultPosition(Vector3D * pos);
	
	void highlight();
	void goToDefault(int speed = 100); // go to default position	
	void undo();

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
	// Position to default to
	Vector3D * _defpos;
	Vector3D * _highlightpos;

	Picture * _north;
	Picture * _south;
	Picture * _east;
	Picture * _west;	

	void calcHighlight(Vector3D * start);
};


#endif			// ARRANGEMENT_H
