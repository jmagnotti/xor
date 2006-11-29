#ifndef TERRAIN_H
#define TERRAIN_H


#include "../shape/Renderable.h"
#include "../shape/Point3D.h"
#include "../shape/Quadrilateral3D.h"
#include "../texture/TextureFactory.h"

/*
 * A lot of work is going to be done here
 */

namespace XOR {

/**
 * This class represents a terrain object. It is basically a 2D array of points. 
 * More functionality should come later, like putting objects "on" the terrain
 * then saying terrain->render() which would render everything that was on the 
 * terrain.
 * **NOT COMPLETE**
 */
class Terrain : public Renderable
{

public:

	////int detailLevel;
	//Quadrilateral3D * terrain[];		// these are the points that actually define the terrain


	/**
	 * Explicit Constructor
	 */
	Terrain(Point3D * point, int diameter);


	/**
	 * Render the terrain
	 */
	void render(void);


protected:
	
	int					_size;
	Quadrilateral3D *	_terrain;

};

}

#endif			// TERRAIN_H

