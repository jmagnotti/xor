#include "../../xor.h"


using namespace XOR;

class CarConfig : public XavierConfiguration
{
public:

	CarConfig() 
	{}

	EventFactory * getEventFactory() const
	{
		return InputEventHandlerFactory::GetInstance();
	}

	const float * getBackgroundColor()
	{
		return Color::DEEP_SKY_BLUE;
	}

	Uint32 getTimerInterval()
	{
		return 30;
	}

	bool isGLFogEnabled()
	{
		return false;
	}
};


class Car : public Object3D
{

public:
	Car(char *filename)
	{
		//static bool initialized = false;
		//_model = ModelFactory::GetInstance()->createModel("resources/f360.ms3d");

		
	//	_model = ModelFactory::GetInstance()->createModel(filename);
	//	_model->incrementStretch(new Vector3D(-.99,-.99,-.99));
	//	_model->incrementRotation(Orientation::THETA, 180.0f);
	}

	Dimension3D * getDimension()
	{
		return new Dimension3D(1,1,1);
	}

	Vector3D * getBaseVector()
	{
		return new Vector3D(0,0,0);
	}

	void renderObject()
	{
		_model->render();
	}

	unsigned int getTimerInterval()
	{
		return 300;
	}

private:

	Model * _model;
};

class Cars 
{

public:

	static const int	 NUM_CARS = 3;
	char label[NUM_CARS][10];
	Controller         * ctrl; 
	//WaypointCollection * track[NUM_CARS+1];
	Car                * car[NUM_CARS];

   /* 
  	* Constructor
 	*/
	Cars(int i, int j)
	{
        ctrl = Controller::GetInstance(new CarConfig());
                
		// < WALL STUFF >
		SDL_ShowCursor(false);
//		ctrl->getCamera()->setWallOffset(i, j);
//		ctrl->getCamera()->setWallMode(Camera::WALL_MODE_STANDARD);
		// </ WALL STUFF >

        //ctrl->getKeyboard()->addListener(this);
		//ctrl->getMouse()->addListener(this);

        ctrl->setModel(new String2D("Car Race Demo"));

	//	ctrl->getCamera()->incrementTranslation(new Vector3D(100,100,100));
	//	ctrl->getCamera()->setFocalPoint(new Vector3D(0,0,0));

#ifdef __ppc__
        ctrl->getCamera()->setCoordinateSystem(
            CoordinateSystemFactory::GetCoordinateSystem(
            CoordinateSystemFactory::MAC_COORDINATE_SYSTEM));
#endif
        
		TextureFactory * factory = TextureFactory::GetInstance();

		HeightField * hf = HeightFieldFactory::GetInstance()->
			buildHeightField(new ImageHeightFieldStrategy("tracks/track01_hf.png"));
		hf->setHeightScale(50.0f);

		hf->setPaint(new Paint(Color::WHITE, Paint::HEIGHT_BASED,
					TextureFactory::GetInstance()->createTexture("tracks/track01_tex32.png")));

		ctrl->getModel()->addObject("field", new CompiledObject3D(hf));

		//track1 = new WaypointCollection("tracks/track01_pts.txt", 1000, 0, true);
		//track2 = new WaypointCollection("tracks/track01_pts.txt", 1000, 0, true);
		//track1 = new WaypointCollection("tracks/track01_pts.txt", 1000, 0, false);
		//track1->print();

	//	for (int i = 0; i < NUM_CARS; i++) {
	//		track[i] = new WaypointCollection("tracks/track01_pts.txt", 1000, 0, true);
			//car[i] = new Car();
	//		switch (i) {
	//			case 0: car[i] = new Car("resources/f360gr.ms3d"); break;
	//			case 1: car[i] = new Car("resources/f360r.ms3d"); break;
	//			case 2: car[i] = new Car("resources/f360y.ms3d"); break;
	//		}
	//		track[i]->initialize(car[i]);
	//		sprintf(label[i], "car%d", i);
	//		ctrl->getModel()->addObject(label[i], car[i]);
	//		car[i]->incrementTranslation(new Vector3D((float)i*0.5f,0,(float)i*1.0f-0.5f));
//		}
//		track[NUM_CARS] = new WaypointCollection("tracks/track01_pts.txt", 1000, 0, true);
//		track[NUM_CARS]->initialize(ctrl->getCamera());
//		ctrl->getCamera()->incrementTranslation(new Vector3D(-3.0f,1.5f,1.5f));
//		ctrl->getCamera()->incrementRotation(Orientation::PHI, -30.0f);
        ctrl->run();
	}

//	void handleKey_p() { ctrl->getCamera()->printWaypoint(); }
	//void handleKey_o() { track1->print(); }
	
//	void handleKey_a() { ctrl->getCamera()->incrementRotation(0, 10.0f, new TimedInterpolation(300,NULL)); }
//	void handleKey_d() { ctrl->getCamera()->incrementRotation(0, -10.0f, new TimedInterpolation(300,NULL)); }
//	void handleKey_w() { ctrl->getCamera()->walk( 0.01f, new TimedInterpolation(300,NULL)); }
//	void handleKey_s() { ctrl->getCamera()->walk(-0.01f, new TimedInterpolation(300,NULL)); }
//	void handleKey_W() { ctrl->getCamera()->walk( 0.05f, new TimedInterpolation(300,NULL)); }
//	void handleKey_S() { ctrl->getCamera()->walk(-0.05f, new TimedInterpolation(300,NULL)); }
//	void handleKey_q() { ctrl->getCamera()->incrementRotation(2, 5.0f, new TimedInterpolation(300,NULL)); }
//	void handleKey_e() { ctrl->getCamera()->incrementRotation(2, -5.0f, new TimedInterpolation(300,NULL)); }
//	void handleKey_c() { ctrl->getCamera()->incrementRotation(1, 5.0f, new TimedInterpolation(300,NULL)); }
//	void handleKey_z() { ctrl->getCamera()->incrementRotation(1, -5.0f, new TimedInterpolation(300,NULL)); }

//	void handleKey_k()
//	{
//		for (int i = 0; i < NUM_CARS; i++)
//			track[i]->apply(car[i]);
//
		//track2->apply(car[1]);
		//ctrl->getCamera()->incrementRotation(Orientation::ROLL, 1020.0f, new TimedInterpolation(6000, NULL));
		//car1->incrementRotation(Orientation::ROLL, 1020.0f, new TimedInterpolation(6000, NULL));
//	}

//	void handleKey_K()
//	{
//		handleKey_k();
////		track[NUM_CARS]->apply(ctrl->getCamera());
//	}
	
//	void handleMouseMotion(MouseMotionEvent * mme)
//	{
//		Mouse * mouse = ctrl->getMouse();
//
//		if (mouse->isLeftButtonDown()) {
//			// rotate camera
//			float xChange = (float)(mouse->getCurrentX() - mouse->getPreviousX()) / 2.0f;
//			float yChange = (float)(mouse->getCurrentY() - mouse->getPreviousY()) / 2.0f;
//
//			ctrl->getCamera()->incrementRotation(
//					Orientation::THETA, -xChange, new TimedInterpolation(100,NULL));
//
//			ctrl->getCamera()->incrementRotation(
//					Orientation::PHI, -yChange, new TimedInterpolation(100,NULL));
//		}
//	}
//	
//	void handleMouseButtonPressed(MouseButtonDown * mbd) { }
//	void handleMouseButtonReleased(MouseButtonUp * mbu) { }

private:

	static const float ROTATE_CHANGE = 5.0f;
	static const float TRANSLATE_CHANGE = 0.2f;
};


/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	if (argc != 3) {
		cout << "usage:\n\tCars <wall-x-offset> <wall-y-offset>" << endl;
	}
	else
	{
		Cars * demo = new Cars(atoi(argv[1]), atoi(argv[2])); 
	}
    return 0;
}

