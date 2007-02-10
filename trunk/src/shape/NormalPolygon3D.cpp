#include "NormalPolygon3D.h"


namespace XOR {

/*
 * Explicit Constructor
 */
NormalPolygon3D::NormalPolygon3D(Vector3D * center, float radius, int numSides){
    
    float x, y;
    GraphicsConversionUtility * gcu;

    gcu = GraphicsConversionUtility::GetInstance();
    _sides = numSides;

    _radius = radius;
    _center = center;
                     
    // x defined by r*cos(theta)
    // y defined by r*sin(theta)
    for(double theta = 0; theta < 360.0; theta+= 360.0/numSides){
        x = radius * cos(theta * gcu->PI/180.0);
        y = radius * sin(theta * gcu->PI/180.0);
                
        _vertices.push_back(new Vector3D(x, y, 0.0));
    }
}

/*
 * Render Method
 */
void NormalPolygon3D::render()
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
 * Default Constructor
 */
NormalPolygon3D::NormalPolygon3D()
{
    _sides = 0;
    _radius = 0.0;
    _center = NULL;
}

}

