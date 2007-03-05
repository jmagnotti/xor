#include "ExtrudedNormalPolygon3D.h"

namespace XOR {


/*
 * Private constructor
 */
ExtrudedNormalPolygon3D::ExtrudedNormalPolygon3D()
{}


/**
 * Extrudes the given NormalPolygon3D along the Z axis to make a 3D Solid.
 */
ExtrudedNormalPolygon3D::ExtrudedNormalPolygon3D(NormalPolygon3D * shape, int depth)
{ 
    buildWithAlias(shape, depth);
}


/**
 * extrude without aliasing
 */
ExtrudedNormalPolygon3D::ExtrudedNormalPolygon3D(NormalPolygon3D * shape, int depth, bool clone)
{
    if(clone)
        buildWithoutAlias(shape, depth);
    else
        buildWithAlias(shape, depth);
}


/**
 * alias the points
 */
void ExtrudedNormalPolygon3D::buildWithAlias(NormalPolygon3D * shape, int depth)
{
    _shape = shape;
    _depth = depth;

    vector<Vector3D*> points = shape->getVertices();

    Vector3D * offset = new Vector3D(0, 0, depth);

    for(int i=0; i < points.size(); i++) {
       _vertices.push_back(points[i]);
       _vertices.push_back( (*(points[i])) + offset);
    }
}


/**
 * clone the points
 */
void ExtrudedNormalPolygon3D::buildWithoutAlias(NormalPolygon3D * shape, int depth)
{
    _shape = shape;
    _depth = depth;

    vector<Vector3D*> points = shape->getVertices();

    Vector3D * offset = new Vector3D(0, 0, depth);

    for(int i=0; i < points.size(); i++) {
       _vertices.push_back(points[i]->clone());
       _vertices.push_back( (*(points[i])) + offset);
    }

}


/**
 * Renders the object.
 */
void ExtrudedNormalPolygon3D::renderObject()
{
    _shape->render();

    glColor3f(.8f,.8f,.8f);

    glBegin(GL_QUAD_STRIP);
        for(int i=0; i<_vertices.size(); i++)
            glVertex3fv(_vertices[i]->toArray());    

        glVertex3fv(_vertices[0]->toArray());
        glVertex3fv(_vertices[1]->toArray());
        
    glEnd();

    glPushMatrix();
        glTranslatef(0,0,_depth);
        _shape->render();
    glPopMatrix();

}


/*
 * return the base of the object
 */
Vector3D * ExtrudedNormalPolygon3D::getBaseVector()
{
    return _shape->getBaseVector();
}


/*
 * NOT CORRECT
 */
Dimension3D * ExtrudedNormalPolygon3D::getDimension()
{
    _shape->getDimension();
}

}

