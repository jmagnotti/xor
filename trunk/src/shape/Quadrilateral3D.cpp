#include "Quadrilateral3D.h"


namespace XOR {

/*
 * Default Constructor.
 * Creates a quad from 0,0,0 to 1,1,0 and a white paint.
 */
Quadrilateral3D::Quadrilateral3D()
{
    /*
    cout << "QUAD DC" << endl;

    _paint = new Paint(Color::WHITE);

	_vertices[0] = new Point3D(0.0f, 0.0f, 0.0f);
	_vertices[1] = new Point3D(0.0f, 1.0f, 0.0f);
	_vertices[2] = new Point3D(1.0f, 1.0f, 0.0f);
	_vertices[3] = new Point3D(1.0f, 0.0f, 0.0f);

	calculateCenter();
    */
}


/*
 * Explicit Constructor.
 * Four corners and a default white paint.
 */
Quadrilateral3D::Quadrilateral3D(Point3D * p0, Point3D * p1, Point3D * p2, Point3D * p3)
{
    _paint = new Paint(Color::WHITE);

	_vertices[0] = p0;		_vertices[1] = p1;
	_vertices[2] = p2;		_vertices[3] = p3;

    // since the dimension constructor is smart enough to correct negative dimensions, we don't need to
    _dimension = new Dimension3D(p2->getX() - p0->getX(),
                                 p2->getY() - p0->getY(),
                                 p2->getZ() - p0->getZ() );
    calculateCenter();
}


/*
 * Explicit Constructor.
 * Four corners and a paint.  */
Quadrilateral3D::Quadrilateral3D(Point3D *p0, Point3D *p1, Point3D *p2, Point3D *p3, Paint *p)
{
	_paint = p;

	_vertices[0] = p0;		_vertices[1] = p1;
	_vertices[2] = p2;		_vertices[3] = p3;

//		setAllColors(p);    //messes up paint set by RectangularPrism.cpp
	calculateCenter();
}

/*
 * Returns the normal associated with the quad, or a point at 0,0,0 if the normal does not exist --
 * this value is not stored as the quads normal.
 */
Point3D * Quadrilateral3D::getNormal()
{
    if (_normal == NULL)
        return new Point3D(1,1,1);

    return _normal;
}


/*
 * Returns the dimension object associated with the quad3D
 */
Dimension3D * Quadrilateral3D::getSize()
{
    return _dimension;
}


/*
 * Draws the quadrilateral.
 * Is doing texture stuff right now, which I may be mixing burdens.
 */
void Quadrilateral3D::render(void)
{

	if(_paint->isTextured())
	{
       	// need to determine if lighting is on and if the object is textured 
		//if (isLit()){
		//	glNormal3fv(getNormal()->getPosition());
		//}

        glColor3fv(_paint->getColorTo());
        glEnable(GL_TEXTURE_2D);

			//activate the texture
            _paint->getTexture()->setActive();
			
            //get the coords from the quad, and use them to create a proper texture spread 
            //fool around with the stretching values
			//should do something like finding the proper values for the quad
			//just take the min of vert[0] and the max of vert[2]. that should work...
			glBegin(GL_QUADS);
				//texture coords in CCW
				glTexCoord2f(0, 1);
				_vertices[0]->render();

				glTexCoord2f(0, 0);
				_vertices[1]->render();

				glTexCoord2f(1, 0);
				_vertices[2]->render();

				glTexCoord2f(1, 1);
				_vertices[3]->render();
			glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    else {
        glBegin(GL_QUADS);
		    _vertices[0]->render();
		    _vertices[1]->render();
		    _vertices[2]->render();
		    _vertices[3]->render();
        glEnd();
	}
}


void Quadrilateral3D::calculateCenter()
{
	_center = new Point3D(	(_vertices[0]->getX() + _vertices[2]->getX()) / 2.0,
							(_vertices[0]->getY() + _vertices[2]->getY()) / 2.0,
							(_vertices[0]->getZ() + _vertices[2]->getZ()) / 2.0	);


	// we first need to find the plane the quad is lying on
	calculateDimension();

	//cout << "the results should be all zeroes: " << endl;
	//cout << _vertices[0]->getX() - _vertices[1]->getX() << "\t" 
	//     << _vertices[1]->getY() - _vertices[2]->getY() << "\t" 
	//     << _vertices[0]->getX() - _vertices[1]->getX() << endl;
}


void Quadrilateral3D::calculateDimension()
{
	float * p0, * p1;
	float len = 0, wid = 0, dep = 0;

	p0 = _vertices[0]->getPosition();
	p1 = _vertices[2]->getPosition();

	// this represents the quads plane
	int plane = 0;

	GraphicsConversionUtility * gcu = GraphicsConversionUtility::GetInstance();

	// first we have to find the plane that the quad lies on. This is done by checking the distance between corresponding 
	// dimensions. If the distance is 0, then that is the plane the quad is laying on.
	//for(int j=0; j<3; j++) {
	//	if (! gcu->compare_f(p0[j], p1[j], .001) ) {
	//		if (j == 0) {

	//			//wid = p1[j] - p0[j];
	//			//_dimension = new Dimension3D(wid, len, 0);
	//		}
	//		else if (j == 1) {
	//		
	//		}
	//		else {
	//		
 //           }
	//	}
	//	//else {
	//	//	plane = j;
	//	//}
	//}
}


/* 
 * assigns the normal for this quad
 */
void Quadrilateral3D::setNormal(Point3D *norm)
{ 
    _normal = norm->invert(); 
}


/*
 * applies the given paint to each vertex.
 * Calls Quadrilateral3D#setAllColors.
 */
void Quadrilateral3D::setPaint(Paint *p)
{
    _paint = p;
	setAllColors(p);		// updates the paint || this will mess up other paint jobs
}


/*
 * Sets a vertex of the quad.
 * This could be used to do interesting transformations
 */
void Quadrilateral3D::setVertex(int vertexNumber, Point3D * newVertex)
{
	_vertices[vertexNumber] = newVertex;
	calculateCenter();
}


/*
 * Sets the color of a particular vertex
 * Pass in the point to set and its color
 */
void Quadrilateral3D::setAllColors(Paint * p)
{
	_paint = p;
	for(int i=0; i<4; i++) 
		_vertices[i]->setColor(_paint->getColorTo());
}


void Quadrilateral3D::print()
{
    for (int i=0; i<4; i++)
       cout << "vert " << i << ": " << _vertices[i]->toString() << endl; 
}

}

