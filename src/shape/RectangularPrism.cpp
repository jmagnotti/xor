#include "RectangularPrism.h"


namespace XOR {

/*
 * Default Constructor
 */
RectangularPrism::RectangularPrism() {
	_paint	= new Paint(Color::WHITE);
	_volume	= new RectangularVolume();
	setup();
}


/*
 * Full control of specs
 */
RectangularPrism::RectangularPrism(Point3D * point, float sizeX, float sizeY, float sizeZ, Paint * p)
{
	_paint	= p;
	_volume	= new RectangularVolume(point, new Dimension3D(sizeX, sizeY, sizeZ));
	setup();
}


/*
 * Explicit Constructor
 */
RectangularPrism::RectangularPrism(RectangularVolume * rv)
{
	_paint	= new Paint(Color::WHITE);
	_volume	= rv;
	setup();
}


/*
 * Calculates the normals for the Rect prism
 */
void RectangularPrism::calculateNormals()
{	
    GraphicsConversionUtility * gcu = GraphicsConversionUtility::GetInstance();

	_normals[0] = gcu->crossProduct(_points[3], _points[7], _points[4]);
	_normals[1] = gcu->crossProduct(_points[2], _points[6], _points[5]);

	_normals[2] = gcu->crossProduct(_points[2], _points[6], _points[7]);
	_normals[3] = gcu->crossProduct(_points[1], _points[5], _points[4]);

	_normals[4] = gcu->crossProduct(_points[7], _points[6], _points[5]);
	_normals[5] = gcu->crossProduct(_points[3], _points[2], _points[1]);

	gcu->normalize(_normals);

	// set the normal for each quad 
	for (int i=0; i<6; i++)
		_faces[i]->setNormal(_normals[i]);
}


/*
 * Sets the color of the RectangularPrism
 */
void RectangularPrism::setPaint(Paint *p)
{
	_paint = p;
	updatePaint();
}


/*
 * Removes a face from the rendering list
 */
void RectangularPrism::removeFace(int faceToRemove)
{
	// make sure the int is valid, get an iterator to the vector, move to the proper place,
	// erase from the vector
	if (faceToRemove <= BOTTOM && faceToRemove >= FRONT)
		_faces.erase(_faces.begin() + faceToRemove);
}


/*
 * calls render on _faces
 */
void RectangularPrism::render(void)
{
//	if (_positioned)
//		_orientation->push();

    push();

	if (true) {
		vector<Quadrilateral3D*>::iterator iter   = _faces.begin();
		vector<Quadrilateral3D*>::iterator finish = _faces.end();
		
		while (iter != finish) {
			(*iter)->render();
			iter++;
		}
	}
	else {
		//glCallList(_displayListID);
	}

    pop();
	
//	if (_positioned)
//		_orientation->pop();
}


/*
 * Initializes the faces of the prism, should use CCW pattern.
 * NOTE: occluded faces will be reset here.
 */
void RectangularPrism::setFaces()
{
	// clear any existing faces
	if (! _faces.empty())
        _faces.clear();

    // FRONT AND BACK
    _faces.push_back(new Quadrilateral3D(_points[3], _points[7], _points[4], _points[0], _paint));		//highZ side
    _faces.push_back(new Quadrilateral3D(_points[2], _points[6], _points[5], _points[1], _paint));		//lowZ side

    // RIGHT AND LEFT
    _faces.push_back(new Quadrilateral3D(_points[2], _points[6], _points[7], _points[3], _paint));		//highXside
    _faces.push_back(new Quadrilateral3D(_points[1], _points[5], _points[4], _points[0], _paint));		//lowXside

    // TOP AND BOTTOM
    _faces.push_back(new Quadrilateral3D(_points[7], _points[6], _points[5], _points[4], _paint));		//highYside
    _faces.push_back(new Quadrilateral3D(_points[3], _points[2], _points[1], _points[0], _paint));		//lowYside
}


/*
 * Control function that Generates _points, applies _paint, and sets up the individual quads
 */
void RectangularPrism::setup()
{
	// use the volume to set the 8 points
	_volume->generatePoints(_points);

	// now apply paint to the points
	updatePaint();

	// initialize the Quad3D array with the points
	setFaces();

	// calculate normals for the quads
	calculateNormals();
}


/*
 * Sets the _paint for the rect prism.
 * This is bad, as it circumvents the painting mechanism of Quad3D. It is necesasry since the 
 * Quad3D mechanism isn't aware of the overall paint of the RectPrism. This should be fixed at some point.
 */
void RectangularPrism::updatePaint()
{
	if (_paint == NULL)
        _paint = new Paint(Color::WHITE);

	// painting order depends on gradient style
	int type = _paint->getGradientStyle();

	switch (type) 
    {
		// all verts get same _paint
		case Paint::NO_GRADIENT:
			for (int i=0; i<8; i++)
				_points[i]->setColor(_paint->getColorTo());
			break;

		// paint based on Z
		case Paint::DEPTH_BASED:	//think about this a bit more
			//for (int i=0; i<8; i++)
			//{
			//	if (i < 4)
			//		_points[i]->setColor(_paint->getColorFrom());
			//	else
			//		_points[i]->setColor(_paint->getColorTo());
			//}
			break;

		// paint based on Y
		case Paint::HEIGHT_BASED:
			for (int i=0; i<8; i++) {
				if (i < 4)
					_points[i]->setColor(_paint->getColorFrom());
				else
					_points[i]->setColor(_paint->getColorTo());
			}
			break;

		// paint based on X
		case Paint::LENGTH_BASED:
			for (int i=0; i<8; i++) {
				if (i == 2 || i == 3 || i == 6 || i == 7 )
					_points[i]->setColor(_paint->getColorFrom());
				else
					_points[i]->setColor(_paint->getColorTo());
			}

			break;
		default:
			break;
	}

}


/*
 * returns registration point
 */
Point3D * RectangularPrism::getRegistrationPoint()
{ 
	return _volume->getRegistrationPoint();	
}


/*
 * returns if the point is within the rect prism
 */
bool RectangularPrism::checkCollision(Point3D * position)
{
	return _volume->contains(position);
}

}

