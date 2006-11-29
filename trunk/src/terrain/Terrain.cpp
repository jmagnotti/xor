#include "Terrain.h"


namespace XOR {

/**
 * Explicit Constructor
 */
Terrain::Terrain(Point3D * point, int diameter)
{
	float x,y,z;
	
	x = point->getX();
	y = point->getY();
	z = point->getZ();

	_terrain = new Quadrilateral3D(
						point, 
						new Point3D(x+diameter, y, z),
						new Point3D(x+diameter, y, z+diameter), 
						new Point3D(x, y, z+diameter));


	Texture * t = TextureFactory::GetInstance()->createTexture("grass.bmp");
	//_terrain->setAllColors(new Paint(t));
    _terrain->setPaint(new Paint(t));
	_size		= diameter;
}


/**
 * Render the terrain
 */
void Terrain::render(void)
{
	_terrain->render();
}

}

