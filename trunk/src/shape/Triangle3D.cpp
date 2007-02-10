#include "Triangle3D.h"


namespace XOR {

/*
 * Default Constructor.
 */
Triangle3D::Triangle3D()
{}


/*
 * Explicit Constructor.
 * Three corners and a default white paint.
 */
Triangle3D::Triangle3D(Vector3D * p0, Vector3D * p1, Vector3D * p2)
{
    _vertices[0] = p0;
    _vertices[1] = p1;
    _vertices[2] = p2;
    _paint = new Paint(Color::WHITE);
}


/*
 * Explicit Constructor.
 * Three corners and a paint.
 */
Triangle3D::Triangle3D(Vector3D * p0, Vector3D * p1, Vector3D * p2, Paint * paint)
{
    _vertices[0] = p0;
    _vertices[1] = p1;
    _vertices[2] = p2;
	_paint = paint;
}

/*
 * Returns the normal associated with the quad, or a point at 0,0,0 if the normal does not exist --
 * this value is not stored as the quads normal.
 */
Vector3D * Triangle3D::getNormal()
{
    if (_normal == NULL)
        return new Vector3D(1,1,1);

    return _normal;
}

/*
 * Returns the dimension object associated with the quad3D
 */
Vector3D * Triangle3D::getOrigin() const
{
    return _vertices[0];
}

/*
 * Returns the dimension object associated with the quad3D
 */
Dimension3D * Triangle3D::getDimension() const
{
    return _dimension;
}


/* 
 * assigns the normal for this quad
 */
void Triangle3D::setNormal(Vector3D * normal)
{ 
    _normal = normal;
}


/*
 * This could be used to do interesting transformations
 */
void Triangle3D::setVertex(int vertexNumber, Vector3D * newVertex)
{
	_vertices[vertexNumber] = newVertex;
}


/*
 * Sets the color of a particular vertex
 * Pass in the point to set and its color
 */
void Triangle3D::setPaint(Paint * p)
{
	_paint = p;
}


char * Triangle3D::toString()
{
	/*
    for (int i=0; i<3; i++)
       cout << "vert " << i << ": " << _vertices[i]->toString() << endl; 
	   */
	return "Not Implemented";
}

void Triangle3D::render()
{
	glColor3f(1,1,1);
    glBegin(GL_TRIANGLES);
		glVertex3fv(_vertices[0]->toArray());	
		glVertex3fv(_vertices[1]->toArray());	
		glVertex3fv(_vertices[2]->toArray());	
	glEnd();
}

}

