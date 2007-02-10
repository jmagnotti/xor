#ifndef TERRAIN_H
#define TERRAIN_H


#include "../shape/Object3D.h"
#include "../geometry/Vector3D.h"
#include "../shape/Quadrilateral3D.h"
#include "../texture/TextureFactory.h"


namespace XOR {

/**
 * This class represents a terrain object. It is basically a 2D array of
 * points. More functionality should come later, like putting objects "on" the
 * terrain.
 * **NOT COMPLETE**
 */
class Terrain : public Object3D
{

public:

	/**
	 * Explicit Constructor
	 */
	Terrain(Vector3D * point, int diameter);


protected:

	/**
	 * Render the terrain
	 */
	void draw();


protected:
	
	int					_size;
	Quadrilateral3D *	_terrain;
	//Quadrilateral3D *	_terrain[]; // should be closer to a height field

};

}

#endif			// TERRAIN_H

