#include "Quadrilateral3D.h"


namespace XOR {

/*
 * find the relative weightings for each extent of each vertex
 */
void Quadrilateral3D::buildWeights(PointScale * scale)
{
    float max[3]; float min[3];

    for (int i=0; i<3; i++)
        max[i] = min[i] = _vertices[0]->get(i);

    for (int i=1; i<4; i++) {
        for (int j=0; j<3; j++) {
            if (_vertices[i]->get(j) > max[j])
                max[j] = _vertices[i]->get(j);
            else if (_vertices[i]->get(j) < min[j])
                min[j] = _vertices[i]->get(j);  
      } 
    } 

    for (int i=0; i<4; i++) {
        _vertexWeights[i] = new Vector3D(
            scale->scaleValue(_vertices[i]->getX(), min[0], max[0]),
            scale->scaleValue(_vertices[i]->getY(), min[1], max[1]),
            scale->scaleValue(_vertices[i]->getZ(), min[2], max[2]) 
        );
    }

    _dimension = new Dimension3D(max[0] - min[0], max[1] - min[1], max[2] - min[2]);
}


/*
 * Default Constructor.
 */
Quadrilateral3D::Quadrilateral3D()
{}


/*
 * Explicit Constructor.
 * Four corners and a default white paint.
 */
Quadrilateral3D::Quadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D * p2, Vector3D * p3, PointScale * scale)
{
    _paint = new Paint();

	// winding order
	_vertices[3] = p3; _vertices[2] = p2;
	_vertices[0] = p0; _vertices[1] = p1;

    buildWeights(scale);
}

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

    PointScale * ps = new PointScale(0,1,1);

    buildWeights(ps);
    delete ps;
}

/*
 * Explicit Constructor.
 * Four corners and a paint.  */
Quadrilateral3D::Quadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D * p2,
		Vector3D * p3, Paint * paint, PointScale * scale)
{
	_paint = paint;

	// winding order
	_vertices[3] = p3; _vertices[2] = p2;
	_vertices[0] = p0; _vertices[1] = p1;

    buildWeights(scale);
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

    PointScale * ps = new PointScale(0,1,1);
    buildWeights(ps);
    delete ps;
}


/*
 * Returns the normal associated with the quad, or a point at 1,1,1 if the
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

	if(_paint->isTextured()) {
       	// need to determine if lighting is on and if the object is textured 
		//if (isLit()){
		//	glNormal3fv(getNormal()->getPosition());
		//}

        glEnable(GL_TEXTURE_2D);

			//activate the texture
            // this must be set before the call th glBegin
            _paint->getTexture()->setActive();
			
            //get the coords from the quad, and use them to create a proper texture spread 
            //fool around with the stretching values
			//should do something like finding the proper values for the quad
			//just take the min of vert[0] and the max of vert[2]. that should work...
			glBegin(GL_QUADS);

				//texture coords in CCW
				glTexCoord2f(1, 1);
                _paint->activateColorAtPosition(_vertexWeights[0]);
				glVertex3fv(_vertices[0]->toArray()); 

				glTexCoord2f(1, 0);
                _paint->activateColorAtPosition(_vertexWeights[1]);
				glVertex3fv(_vertices[1]->toArray());

				glTexCoord2f(0, 0);
                _paint->activateColorAtPosition(_vertexWeights[2]);
				glVertex3fv(_vertices[2]->toArray());

				glTexCoord2f(0, 1);
                _paint->activateColorAtPosition(_vertexWeights[3]);
				glVertex3fv(_vertices[3]->toArray());

			glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    else {
        glBegin(GL_QUADS);
            _paint->activateColorAtPosition(_vertexWeights[0]);
            glVertex3fv(_vertices[0]->toArray());

            _paint->activateColorAtPosition(_vertexWeights[1]);
            glVertex3fv(_vertices[1]->toArray());

            _paint->activateColorAtPosition(_vertexWeights[2]);
            glVertex3fv(_vertices[2]->toArray());

            _paint->activateColorAtPosition(_vertexWeights[3]);
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

