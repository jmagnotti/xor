class MultiPaintPrism : public RectangularPrism
{

public:

	MultiPaintPrism(Vector3D * origin, Dimension3D * size, Paint * paints[6])
	{
		_volume = new RectangularVolume(origin, size);
		build(paints);
	}

	void build(Paint * paints[6])
	{
		_order[0] = BOTTOM;
		_order[1] = REAR;
		_order[2] = RIGHT;
		_order[3] = LEFT;
		_order[4] = FRONT;
		_order[5] = TOP;

		// use the volume to set the 8 points
		_volume->generatePoints(_points);
		// we need a a PointScale that will default to 0 for the Quads that are on
		// the "low" end of the dimension
		PointScale   * psLow  = new PointScale(0,1,0);
		PointScale   * psHigh = new PointScale(0,1,1);

		// a texture scaler for the sides that should be mapped according to their
		// XY. These quad has no Z extent.
		TextureScale * tsXY = new TextureScale(
				new Vector2D(_points[0]->getX(),  _points[0]->getY()), 

				new Dimension2D(_points[7]->getX() - _points[0]->getX(), 
								_points[7]->getY() - _points[0]->getY()),

				TextureScale::X_AND_Y, 
				TextureScale::STRETCHED);

		// a texture scaler for the sides that should be mapped according to their
		// XZ. These quad has no Y extent.
		TextureScale * tsXZ = new TextureScale(
				new Vector2D(_points[0]->getX(),  _points[0]->getZ()), 

				new Dimension2D(_points[2]->getX() - _points[0]->getX(), 
								_points[2]->getZ() - _points[0]->getZ()),

				TextureScale::X_AND_Z, 
				TextureScale::STRETCHED);

		// a texture scaler for the sides that should be mapped according to their
		// YZ. These quad has no X extent.
		TextureScale * tsYZ = new TextureScale(
				new Vector2D(_points[0]->getY(),  _points[0]->getZ()), 

				new Dimension2D(_points[5]->getY() - _points[0]->getY(), 
								_points[5]->getZ() - _points[0]->getZ()),

				TextureScale::Z_AND_Y, 
				TextureScale::STRETCHED);

		// clear any existing faces
		// #FIXME memory leak potential
		if (! _faces.empty())
			_faces.clear();


		/* Cube Configuration:

		   5---------6     
		  /         /|
		 4---------7 |
		 |         | |
		 | 1-------|-2
		 |/        |/
		 0---------3

		*/


		// TOP AND BOTTOM
		_faces[TOP]    = new Quadrilateral3D(_points[7], _points[6], _points[5], _points[4], paints[0], psHigh, tsXZ);	    	//highYside
		_faces[BOTTOM] = new Quadrilateral3D(_points[3], _points[2], _points[1], _points[0], paints[1], psLow, tsXZ);	//lowYside

		// RIGHT AND LEFT
		_faces[RIGHT]  = new Quadrilateral3D(_points[2], _points[6], _points[7], _points[3], paints[2], psHigh, tsYZ);  	      	//highXside
		_faces[LEFT]   = new Quadrilateral3D(_points[1], _points[5], _points[4], _points[0], paints[3], psLow, tsYZ);	//lowXside

		// FRONT AND BACK
		_faces[FRONT]  = new Quadrilateral3D(_points[3], _points[7], _points[4], _points[0], paints[4], psHigh, tsXY);    		//highZ side
		_faces[REAR]   = new Quadrilateral3D(_points[2], _points[6], _points[5], _points[1], paints[5], psLow, tsXY);	//lowZ side

	}

};
