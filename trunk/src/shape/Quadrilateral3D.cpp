#include "Quadrilateral3D.h"


namespace XOR {

/*
 * find the relative weightings for each extent of each vertex
 */
void Quadrilateral3D::buildWeights()
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

    _dimension = new Dimension3D(
            max[0] - min[0], max[1] - min[1], max[2] - min[2]);

    for (int i=0; i<4; i++) {
        _vertexColorWeights[i] = new Vector3D(
            _colorScale->scaleValue(_vertices[i]->getX(), min[0], max[0]),
            _colorScale->scaleValue(_vertices[i]->getY(), min[1], max[1]),
            _colorScale->scaleValue(_vertices[i]->getZ(), min[2], max[2]) 
        );
    }

    if (_textureScale != NULL) {
        switch (_textureScale->getMappingRule()) {

            case TextureScale::X_AND_Y:
                for (int i=0; i<4; i++) {
                    _vertexTextureWeights[i] = new Vector2D( 
                            _textureScale->scaleU(_vertices[i]->getX()),
                            _textureScale->scaleV(_vertices[i]->getY()));
                }
                break;

            case TextureScale::X_AND_Z:
                for (int i=0; i<4; i++) {
                    _vertexTextureWeights[i] = new Vector2D( 
                            _textureScale->scaleU(_vertices[i]->getX()),
                            _textureScale->scaleV(_vertices[i]->getZ()));
                }
                break;

            case TextureScale::Y_AND_Z:
                for (int i=0; i<4; i++) {
                    _vertexTextureWeights[i] = new Vector2D( 
                            _textureScale->scaleU(_vertices[i]->getY()),
                            _textureScale->scaleV(_vertices[i]->getZ()));
                }
                break;
        }    
    }
    else { // this feels dirty
        for (int i=0; i<4; i++)
            _vertexTextureWeights[i] = new Vector2D(0,0);
    }

    _baseVector = new Vector3D(min);
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
Quadrilateral3D::Quadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D * p2, Vector3D * p3)
{
    _colorScale   = new PointScale(0,1,1);
    _textureScale = NULL;

    _paint = new Paint();

	// winding order
	_vertices[3] = p3; _vertices[2] = p2;
	_vertices[0] = p0; _vertices[1] = p1;

    buildWeights();
}

/*
 * Explicit Constructor.
 * Four corners and a paint.  
 */
Quadrilateral3D::Quadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D * p2,
		Vector3D * p3, Paint * paint, PointScale * colorScale, TextureScale * textureScale)
{
    _colorScale   = colorScale;
    _textureScale = textureScale;

	_paint = paint;

	// winding order
	_vertices[3] = p3; _vertices[2] = p2;
	_vertices[0] = p0; _vertices[1] = p1;

    buildWeights();
}


/*
 * Explicit Constructor.
 * Four corners and a paint.  
 */
Quadrilateral3D::Quadrilateral3D(Vector3D * p0, Vector3D * p1, Vector3D * p2,
		Vector3D * p3, Paint * paint)
{
    _colorScale   = new PointScale(0,1,1);
    _textureScale = NULL;

	_paint = paint;

	// winding order
	_vertices[3] = p3; _vertices[2] = p2;
	_vertices[0] = p0; _vertices[1] = p1;

    buildWeights();
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
 */
void Quadrilateral3D::renderObject()
{
    _paint->activate();
    
    //if(isLit())  
        //glNormal3fv(_normals[i]->toArray());

	int texCoords[4] = {2, 3, 0, 1};

    glBegin(GL_QUADS);
        for(int i=0; i<4; i++) {
            _paint->activateTextureAtPosition(_vertexTextureWeights[texCoords[i]]);
            _paint->activateColorAtPosition(_vertexColorWeights[i]);
            glVertex3fv(_vertices[i]->toArray()); 
        }
    glEnd();

    _paint->deactivate();
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
    if (vertexNumber >= 0 && vertexNumber < 4) {
        Vector3D * removed = _vertices[vertexNumber];
        _vertices[vertexNumber] = newVertex;

        delete removed;
    }

    // without the PointScale and TextureScale this is impossible, we need to
    // clone & save them
    //buildWeights();
}


/*
 * set the paint for the object
 */
void Quadrilateral3D::setPaint(Paint * paint)
{
	_paint = paint;
}


/*
 * return a clone of the paint
 */
Paint * Quadrilateral3D::getPaint() const
{
    return _paint;
}


/*
 * Print vertex data from Quadrilateral3D
 */
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
    return _baseVector->clone();
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

