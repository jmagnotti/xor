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
	void unhighlight();
	void goToDefault(int speed = 100); // go to default position	
	void focus();
	void unfocus();

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
	
	// not actually the highlight position
	// its a vector to translate by to higlight
	Vector3D * _highlight;
	Vector3D * _unhighlight;

	// the vectors need to translate to focus
	// and unfocus
	Vector3D * _focus;
	Vector3D * _unfocus;
	void calcFocus(Vector3D * start);

	Picture * _north;
	Picture * _south;
	Picture * _east;
	Picture * _west;	
};


#endif			// ARRANGEMENT_H
