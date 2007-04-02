#include "../../xor.h"


using namespace XOR;

class Car : public Object3D
{
	public:
		Car()
		{
			_model = ModelFactory::GetInstance()->createModel("resources/f360.ms3d");
			_model->incrementStretch(new Vector3D(-.9,-.9,-.9));
			_model->incrementRotation(Orientation::THETA, 180.0f);
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

	private:
		Model * _model;
};

class Cars : public DefaultKeyboardListener, public DefaultMouseListener
{

public:

	Controller         * ctrl; 
	WaypointCollection * track1;
	Car                * car1;

   /* 
  	* Constructor
 	*/
	Cars()
	{
        ctrl = Controller::GetInstance(new XavierConfiguration());
                
               // InputEventHandlerFactory::GetInstance());
        ctrl->defaultConfiguration();

		Timer::SetInterval(30);

        ctrl->getKeyboard()->addListener(this);
		ctrl->getMouse()->addListener(this);

        ctrl->setModel(new String2D("Car Race Demo"));

		ctrl->getCamera()->incrementTranslation(new Vector3D(100,100,100));
		ctrl->getCamera()->setFocalPoint(new Vector3D(0,0,0));

#ifdef __ppc__
        ctrl->getCamera()->setCoordinateSystem(
            CoordinateSystemFactory::GetCoordinateSystem(
            CoordinateSystemFactory::MAC_COORDINATE_SYSTEM));
#endif
        
        //glDisable(GL_DEPTH_TEST);
        glDisable(GL_LINE_SMOOTH);
        glDisable(GL_BLEND);
		glDisable(GL_FOG);
		
		TextureFactory * factory = TextureFactory::GetInstance();

		HeightField * hf = HeightFieldFactory::GetInstance()->
			buildHeightField(new ImageHeightFieldStrategy("tracks/track01_hf.png"));
		hf->setHeightScale(50.0f);

		hf->setPaint(new Paint(Color::WHITE, Paint::HEIGHT_BASED,
					TextureFactory::GetInstance()->createTexture("tracks/track01_tex32.png")));

		ctrl->getModel()->addObject("field", new CompiledObject3D(hf));

		track1 = new WaypointCollection("tracks/track01_pts.txt", 1000, 0);

		car1 = new Car();
		track1->initialize(car1);
		ctrl->getModel()->addObject("car1", car1);
		//track1->initialize(ctrl->getCamera());

        ctrl->run();
	}

	void handleKey_p() { ctrl->getCamera()->printWaypoint(); }

	void handleKey_a() { ctrl->getCamera()->incrementRotation(0, 10.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_d() { ctrl->getCamera()->incrementRotation(0, -10.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_w() { ctrl->getCamera()->walk( 0.11f, new TimedInterpolation(300,NULL)); }
	void handleKey_s() { ctrl->getCamera()->walk(-0.11f, new TimedInterpolation(300,NULL)); }
	void handleKey_q() { ctrl->getCamera()->incrementRotation(2, 5.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_e() { ctrl->getCamera()->incrementRotation(2, -5.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_c() { ctrl->getCamera()->incrementRotation(1, 5.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_z() { ctrl->getCamera()->incrementRotation(1, -5.0f, new TimedInterpolation(300,NULL)); }

	void handleKey_k()
	{
		cout << "handling..." << endl;
		track1->apply(car1);
		//track1->apply(ctrl->getCamera());
		//ctrl->getCamera()->incrementRotation(Orientation::ROLL, 1020.0f, new TimedInterpolation(6000, NULL));
		//car1->incrementRotation(Orientation::ROLL, 1020.0f, new TimedInterpolation(6000, NULL));
	}
	
	void handleMouseMotion(MouseMotionEvent * mme)
	{
		Mouse * mouse = ctrl->getMouse();

		if (mouse->isLeftButtonDown()) {
			// rotate camera
			float xChange = (float)(mouse->getCurrentX() - mouse->getPreviousX()) / 2.0f;
			float yChange = (float)(mouse->getCurrentY() - mouse->getPreviousY()) / 2.0f;

			ctrl->getCamera()->incrementRotation(
					Orientation::THETA, -xChange, new TimedInterpolation(100,NULL));
			ctrl->getCamera()->incrementRotation(
					Orientation::PHI, -yChange, new TimedInterpolation(100,NULL));
		}
	}
	
	void handleMouseButtonPressed(MouseButtonDown * mbd) { }
	void handleMouseButtonReleased(MouseButtonUp * mbu) { }
	
private:

	static const float ROTATE_CHANGE = 5.0f;
	static const float TRANSLATE_CHANGE = 0.2f;
};


/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	Cars * demo = new Cars(); 
    return 0;
}

