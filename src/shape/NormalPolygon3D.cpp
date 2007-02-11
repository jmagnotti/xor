#include "NormalPolygon3D.h"


namespace XOR {

/*
 * Explicit Constructor
 */
NormalPolygon3D::NormalPolygon3D(Vector3D * center, float radius, int
		numSides){
    
    float x, y, z;
    GraphicsConversionUtility * gcu;

    gcu = GraphicsConversionUtility::GetInstance();
    _sides = numSides;

	if 		(_sides < 3) 	_sides = 3;
	else if (_sides > 100)  _sides = 100;

    _radius = radius;
    _center = center;
                     
    // x defined by r*cos(theta)
    // y defined by r*sin(theta)
	z = center->getZ();
    for(double theta = 0; theta < 360.0; theta+= 360.0/_sides){
        x = radius * cos(theta * gcu->PI/180.0);
        y = radius * sin(theta * gcu->PI/180.0);
                
        _vertices.push_back(new Vector3D(x,y,z));
    }
}

/*
 * Render Method
 */
void NormalPolygon3D::renderObject()
{
    glColor3f(1, 1, 1);

    glBegin(GL_TRIANGLE_FAN);
		for(int i = 0; i < _vertices.size(); i++)
		   glVertex3fv(_vertices[i]->toArray()); 
    glEnd();
}

/*
 * Set Paint Object
 */
void NormalPolygon3D::setPaint(Paint * paint)
{
    _paint = paint;
}

/*
 * return _radius*2
 */
Dimension3D * NormalPolygon3D::getDimension()
{
	return new Dimension3D(_radius*2);
}

/*
 * return a clone of the center
 */
Vector3D * NormalPolygon3D::getBaseVector()
{
	return new Vector3D(_center->getX(), _center->getY(), _center->getZ());
}

}

