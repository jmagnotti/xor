#include "../../xor.h"
#include <stdlib.h>


using namespace XOR;


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



/**
 * Shows the simplicity of XOR
 */
int main(int argc, char ** argv)
{

#ifdef __ppc__
	CoordinateSystemFactory::SetDefaultCoordinateSystem(
			CoordinateSystemFactory::MAC_COORDINATE_SYSTEM);
#endif

    // We need a reference to the controller, get it through the static
    // accessor method. This method ensures that all requestors get the same
    // controller object (note: Singleton Pattern).
    // tell the controller to setup friendly defaults for us. This includes
    // mouse, keyboard, view, and reshape defaults. It also sets up openGL 
    // parameters. To only setup I/O and windowing, pass false to the method,
    // then setup openGL parameters yourself. Check out the documentation for
    // Controller::defaultConfiguration(...) for details about exactly what 
    // gets setup.

    Controller * ctrl = Controller::GetInstance(new XavierConfiguration());

    // Add a keyboard listener that has a small set of key handlers
	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
	ctrl->getMouse()->addListener(new DefaultMouseListener());

    //Triangle3D * hello = new Triangle3D(new Vector3D(-.25,-.25,-1), new Vector3D(.25,-.25,-1), new Vector3D(.25,.25,-1));
    //NormalPolygon3D * hello = new NormalPolygon3D(new Vector3D(.5,.5,-2.5), 0.5, 4);
	Paint * paints[6];

	TextureFactory * tf = TextureFactory::GetInstance();
	paints[0] = new Paint(tf->createTexture("face0.bmp"));
	paints[1] = new Paint(tf->createTexture("face1.bmp"));
	paints[2] = new Paint(tf->createTexture("face2.bmp"));
	paints[3] = new Paint(tf->createTexture("face3.bmp"));
	paints[4] = new Paint(tf->createTexture("face4.bmp"));
	paints[5] = new Paint(tf->createTexture("face5.bmp"));

	MultiPaintPrism  * mpc = new MultiPaintPrism(
			new Vector3D(0,0,0), new Dimension3D(2,2,2), paints);

    //hello->incrementRotation(Orientation::THETA, 90);
	//CompiledObject3D * co = new CompiledObject3D(new ExtrudedNormalPolygon3D(hello, 5));
	
    // the controller will detect this is not a "WORLD" object
    // and automatically wrap it inside of one (how convenient!)
    String2D * str  = new String2D("Hello", 200,200);

    str->setFont(BITMAP_FONT_TYPE_TIMES_ROMAN_24);
    ctrl->setModel(str);
            

	/* 
	 new Rectangle2D(new Vector2D(300,300), 
		   new Vector2D(500,500), 
		   new Paint(Color::RED, Color::WHITE, Paint::HEIGHT_BASED)));
     */

	ctrl->getModel()->addObject("I hate C++", mpc);

    // this call runs the demo.
    ctrl->run();

    // this return never happens, as clean up is done elsewhere.
    // this means you don't need to delete hello, it's memory will
    // be freed by the Controller
    return 0;
}

