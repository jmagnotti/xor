#include "Quadrilateral3D.h"


namespace XOR {

/*
 * Default Constructor.
 */
Quadrilateral3D::Quadrilateral3D()
{}


/*
 * Explicit Constructor.
 * Four corners and a default white paint.
 */
Quadrilateral3D::Quadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D * p2, Vector3D * p3)
{
    _paint = new Paint();

	// winding order
	_vertices[3] = p3; _vertices[2] = p2;
	_vertices[0] = p0; _vertices[1] = p1;

	// since the dimension constructor is smart enough to correct negative
	// dimensions, we don't need to
    _dimension = new Dimension3D(p2->getX() - p0->getX(),
                                 p2->getY() - p0->getY(),
                                 p2->getZ() - p0->getZ() );
    //calculateCenter();
}


/*
 * Explicit Constructor.
 * Four corners and a paint.  */
Quadrilateral3D::Quadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D * p2,
		Vector3D * p3, Paint * paint)
{
	_paint = paint;

	// winding order
	_vertices[3] = p3; _vertices[2] = p2;
	_vertices[0] = p0; _vertices[1] = p1;
}

/*
 * Returns the normal associated with the quad, or a point at 0,0,0 if the
 * normal does not exist -- this value is not stored as the quads normal.
 */
Vector3D * Quadrilateral3D::getNormal() const
{
    if (_normal == NULL)
        return new Vector3D(1,1,1);

    return _normal;
}


/*
 * Draws the quadrilateral.
 * Is doing texture stuff right now, which I may be mixing burdens.
 */
void Quadrilateral3D::renderObject()
{
	glColor3fv(_paint->getColorTo());

	if(_paint->isTextured())
	{
       	// need to determine if lighting is on and if the object is textured 
		//if (isLit()){
		//	glNormal3fv(getNormal()->getPosition());
		//}

        glEnable(GL_TEXTURE_2D);

			//activate the texture
            _paint->getTexture()->setActive();
			
            //get the coords from the quad, and use them to create a proper texture spread 
            //fool around with the stretching values
			//should do something like finding the proper values for the quad
			//just take the min of vert[0] and the max of vert[2]. that should work...
			glBegin(GL_QUADS);

				//texture coords in CCW
				glTexCoord2f(1, 1);
				glVertex3fv(_vertices[0]->toArray()); 

				glTexCoord2f(1, 0);
				glVertex3fv(_vertices[1]->toArray());

				glTexCoord2f(0, 0);
				glVertex3fv(_vertices[2]->toArray());

				glTexCoord2f(0, 1);
				glVertex3fv(_vertices[3]->toArray());

			glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    else {
        glBegin(GL_QUADS);
				glVertex3fv(_vertices[0]->toArray());
				glVertex3fv(_vertices[1]->toArray());
				glVertex3fv(_vertices[2]->toArray());
				glVertex3fv(_vertices[3]->toArray());
        glEnd();
	}
}


/* 
 * assigns the normal for this quad
 */
void Quadrilateral3D::setNormal(Vector3D * normal)
{ 
    _normal = normal;
}


/*
 * Sets a vertex of the quad.
 * This could be used to do interesting transformations
 */
void Quadrilateral3D::setVertex(int vertexNumber, Vector3D * newVertex)
{
	_vertices[vertexNumber] = newVertex;
}


/*
 * set the paint for the object
 */
void Quadrilateral3D::setPaint(Paint * paint)
{
	_paint = paint;
}


void Quadrilateral3D::print()
{
    for (int i=0; i<4; i++)
	   cout << "vert " << i << ": " << _vertices[i]->toString() << endl; 
}


/**
 * return a clone of the base point
 */
Vector3D * Quadrilateral3D::getBaseVector()
{
	return new Vector3D(_vertices[0]->getX(), _vertices[0]->getY(),
			_vertices[0]->getZ());
}


/*
 * return a clone of the size
 */
Dimension3D * Quadrilateral3D::getDimension()
{
	return new Dimension3D(_dimension->getWidth(), _dimension->getHeight(),
			_dimension->getDepth());
}


}

