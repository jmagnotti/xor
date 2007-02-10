#include "Terrain.h"


namespace XOR {

/**
 * Explicit Constructor
 */
Terrain::Terrain(Vector3D * point, int diameter)
{
	float x,y,z;
	
	x = point->getX();
	y = point->getY();
	z = point->getZ();

	_terrain = new Quadrilateral3D( point, 
						new Vector3D(x+diameter, y, z),
						new Vector3D(x+diameter, y, z+diameter), 
						new Vector3D(x, y, z+diameter));


	//Texture * t = TextureFactory::GetInstance()->createTexture("grass.bmp");
   
    //_terrain->setPaint(new Paint(t));
	_size		= diameter;
}


/**
 * Render the terrain
 */
void Terrain::draw(void)
{
	_terrain->render();
}

}

