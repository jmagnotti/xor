#include "RectangularPrism.h"


namespace XOR {

	const int RectangularPrism::TOP	    = 0;
	const int RectangularPrism::BOTTOM	= 1;
	const int RectangularPrism::RIGHT	= 2;
	const int RectangularPrism::LEFT	= 3;
	const int RectangularPrism::FRONT	= 4;
	const int RectangularPrism::REAR	= 5;

/*
 * Default Constructor
 */
RectangularPrism::RectangularPrism() 
{}


/*
 * Full control of specs
 */
RectangularPrism::RectangularPrism(Vector3D * point, float sizeX, float sizeY,
		float sizeZ, Paint * paint)
{
	_paint	= paint;
	_volume	= new RectangularVolume(point, new Dimension3D(sizeX, sizeY, sizeZ));
	setup();
}

RectangularPrism::RectangularPrism(Vector3D * point, Dimension3D * size, Paint * paint)
{
    _paint = paint;
    _volume = new RectangularVolume(point, size);
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

	_normals[FRONT]  = gcu->crossProduct(_points[3], _points[7], _points[4]);
	_normals[REAR]   = gcu->crossProduct(_points[2], _points[6], _points[5]);

	_normals[RIGHT]  = gcu->crossProduct(_points[2], _points[6], _points[7]);
	_normals[LEFT]   = gcu->crossProduct(_points[1], _points[5], _points[4]);

	_normals[TOP]    = gcu->crossProduct(_points[7], _points[6], _points[5]);
	_normals[BOTTOM] = gcu->crossProduct(_points[3], _points[2], _points[1]);

	gcu->normalize(_normals);

    for(int i=0; i<_faces.size(); i++)
        _faces[i]->setNormal(_normals[i]);

    //map<const int, Quadrilateral3D*>::iterator iter = _faces.begin();
    //map<const int, Quadrilateral3D*>::iterator end  = _faces.end();

    //while (iter != end) {
        //iter->second->setNormal(_normals[iter->first]);
        //++iter;
    //}
}


/*
 * Sets the color of the RectangularPrism
 * #FIXME this is not the expected behavior
 */
void RectangularPrism::setPaint(Paint * paint)
{
	_paint = paint;

    for(int i=0; i<_faces.size(); i++)
        _faces[i]->setPaint(paint);

    /*
        map<const int, Quadrilateral3D*>::iterator iter = _faces.begin();
        map<const int, Quadrilateral3D*>::iterator end  = _faces.end();

        while (iter != end) {
            iter->second->setPaint(paint);
            ++iter;
        }
    */

}


/*
 * Removes a face from the rendering collection
 */
Quadrilateral3D * RectangularPrism::removeFace(const int faceToRemove)
{
    Quadrilateral3D * removedFace = NULL;

    //cout << "Trying to remove face: " << faceToRemove << endl;
    // make sure the int is a valid face
	if (faceToRemove <= RectangularPrism::REAR && faceToRemove >= RectangularPrism::TOP) {
        removedFace = _faces[faceToRemove];
        _faces[faceToRemove] = NULL;
    }

    return removedFace;
}


/*
 * calls render on _faces
 */
void RectangularPrism::renderObject()
{
    /*
     * Rendering order is important, so the map just won't do
	map<const int, Quadrilateral3D*>::iterator iter   = _faces.begin();
	map<const int, Quadrilateral3D*>::iterator finish = _faces.end();
	
	while (iter != finish) {
		iter->second->render();
		++iter;
	}
    */

    
    //cout << "id: " << this << " RectangularPrism::renderObject" << "at : " << getBaseVector()->toString() << endl;

    for (int i=0; i<6; i++) {
        if (_faces[_order[i]] != NULL) 
            _faces[_order[i]]->render();
    }

}


/*
 * Initializes the faces of the prism, should use CCW pattern.
 * NOTE: occluded faces will be reset here.
 */
void RectangularPrism::setFaces()
{
	// we need a a PointScale that will default to 0 for the Quads that are on
    // the "low" end of the dimension
    PointScale   * psLow  = new PointScale(0,1,0);
    PointScale   * psHigh = new PointScale(0,1,1);

    // a texture scaler for the sides that should be mapped according to their
    // XY. These quads have no Z extent.
    TextureScale * tsXY = new TextureScale(
            new Vector2D(_points[0]->getX(),  _points[0]->getY()), 

            new Dimension2D(_points[7]->getX() - _points[0]->getX(), 
                            _points[7]->getY() - _points[0]->getY()),

            TextureScale::X_AND_Y, 
            TextureScale::TILED);

    // a texture scaler for the sides that should be mapped according to their
    // XZ. These quads have no Y extent.
    TextureScale * tsXZ = new TextureScale(
            new Vector2D(_points[0]->getX(),  _points[0]->getZ()), 

            new Dimension2D(_points[2]->getX() - _points[0]->getX(), 
                            _points[2]->getZ() - _points[0]->getZ()),

            TextureScale::X_AND_Z, 
            TextureScale::TILED);

    // a texture scaler for the sides that should be mapped according to their
    // YZ. These quads have no X extent.
    TextureScale * tsYZ = new TextureScale(
            new Vector2D(_points[0]->getY(),  _points[0]->getZ()), 

            new Dimension2D(_points[5]->getY() - _points[0]->getY(), 
                            _points[5]->getZ() - _points[0]->getZ()),

            TextureScale::Z_AND_Y, 
            TextureScale::TILED);

	// clear any existing faces
    // #FIXME memory leak potential
//	if  (_faces.size() > 0)
//        _faces.clear();


    /* Cube Configuration:

       5---------6     
      /         /|
     4---------7 |
     |         | |
     | 1-------|-2
     |/        |/
     0---------3

    */
//cout << "Ready to set faces" << endl;

    // TOP AND BOTTOM
    _faces.push_back(new Quadrilateral3D(_points[7], _points[6], _points[5], _points[4], _paint, psHigh, tsXZ));	//highYside
    _faces.push_back(new Quadrilateral3D(_points[3], _points[2], _points[1], _points[0], _paint, psLow, tsXZ));	//lowYside

    // RIGHT AND LEFT
    _faces.push_back(new Quadrilateral3D(_points[2], _points[6], _points[7], _points[3], _paint, psHigh, tsYZ)); //highXside
    _faces.push_back(new Quadrilateral3D(_points[1], _points[5], _points[4], _points[0], _paint, psLow, tsYZ));	//lowXside

    // FRONT AND BACK
    _faces.push_back(new Quadrilateral3D(_points[3], _points[7], _points[4], _points[0], _paint, psHigh, tsXY)); //highZ side
    _faces.push_back(new Quadrilateral3D(_points[2], _points[6], _points[5], _points[1], _paint, psLow, tsXY));	//lowZ side
}


/*
 * sets the rendering order. 
 */
void RectangularPrism::setRenderingOrder(int order [6])
{
    for (int i=0; i<6; i++)
        _order[i] = order[i];
}

/*
 * Control function that Generates _points, applies _paint, and sets up the individual quads
 */
void RectangularPrism::setup()
{
    _order[0] = BOTTOM;
    _order[1] = REAR;
    _order[2] = RIGHT;
    _order[3] = LEFT;
    _order[4] = FRONT;
    _order[5] = TOP;
    
	// use the volume to set the 8 points
	_volume->generatePoints(_points);

	// initialize the Quad3D array with the points
	setFaces();

	// calculate normals for the quads
	calculateNormals();
}


/*
 * returns registration point
 */
Vector3D * RectangularPrism::getBaseVector()
{ 
	return _volume->getOrigin();	
}


/*
 * returns if the point is within the rect prism
 */
bool RectangularPrism::checkCollision(Vector3D * position)
{
	return _volume->contains(position);
}


void RectangularPrism::printInfo()
{
    //map<const int, Quadrilateral3D*>::iterator iter   = _faces.begin();
    //map<const int, Quadrilateral3D*>::iterator finish = _faces.end();
    
    //while (iter != finish) {
        //iter->second->print();
        //++iter;
    //}
    for(int i=0;i<_faces.size();i++) {
        if (_faces[i] != NULL)
            _faces[i]->print();
    }
}


/*
 *
 */
Dimension3D * RectangularPrism::getDimension()
{
	return _volume->getDimension();
}

}

