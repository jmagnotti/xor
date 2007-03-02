#include "../../xor.h"


using namespace XOR;


class CoordinateSystemDemo : public DefaultKeyboardListener, DefaultMouseListener
{

public:

	Controller * ctrl; 

   /* 
  	* Constructor
 	*/
	CoordinateSystemDemo()
	{
		_systype = 0;

        ctrl = Controller::GetInstance(InputEventProxyFactory::GetInstance());
        ctrl->defaultConfiguration();

		//ctrl->removeDefaultKeyboardListener();
        ctrl->getKeyboard()->addListener(this);
		//ctrl->removeDefaultMouseListener();
		ctrl->getMouse()->setDefaultMouseListener(this);

        ctrl->setModel(new String2D("Coordinate Test (press 'x' to switch axes)"));

		ctrl->getViewer()->incrementTranslation(new Vector3D(10,10,10));
		ctrl->getViewer()->setFocalPoint(new Vector3D(0,0,0));
        
		TextureFactory * factory = TextureFactory::GetInstance();
		
		ctrl->getModel()->addObject("white", 
				new CompiledObject3D(new Cube(
						new Vector3D(.5,.5,.5), 1, 
						new Paint(Color::WHITE, Paint::HEIGHT_BASED, 
							factory->createTexture("images/white.png")))));
		ctrl->getModel()->addObject("blue",	 
				new CompiledObject3D(new Cube(
						new Vector3D(0,0,5), 1, 
						new Paint(Color::WHITE, Paint::HEIGHT_BASED, 
							factory->createTexture("images/z_blue.png")))));
		ctrl->getModel()->addObject("green", 
				new CompiledObject3D(new Cube(
						new Vector3D(0,5,0), 1, 
						new Paint(Color::WHITE, Paint::HEIGHT_BASED, 
							factory->createTexture("images/y_green.png")))));
		ctrl->getModel()->addObject("red", 	 
				new CompiledObject3D(new Cube(
						new Vector3D(5,0,0), 1, 
						new Paint(Color::WHITE, Paint::HEIGHT_BASED, 
							factory->createTexture("images/x_red.png")))));

        ctrl->run();
	}

	void handleKey_l()
	{
		cout << "LOOK AT ORIGIN" << endl;
		ctrl->getViewer()->setFocalPoint(new Vector3D(0,0,0));
	}

	void handleKey_x()
	{
		_systype = (_systype+1)%4;

		if (_systype == 1)
		{
			std::cout << "SWITCH COORD SYSTEM: MATH" << endl;
			ctrl->getViewer()->setCoordinateSystem(CoordinateSystemFactory::GetCoordinateSystem(CoordinateSystemFactory::MATH_COORDINATE_SYSTEM));
		}
		else if (_systype == 2)
		{
			std::cout << "SWITCH COORD SYSTEM: LEFT OPENGL" << endl;
			ctrl->getViewer()->setCoordinateSystem(CoordinateSystemFactory::GetCoordinateSystem(CoordinateSystemFactory::LEFT_OPENGL_COORDINATE_SYSTEM));
		}
		else if (_systype == 3)
		{
			std::cout << "SWITCH COORD SYSTEM: ENGINEER" << endl;
			ctrl->getViewer()->setCoordinateSystem(CoordinateSystemFactory::GetCoordinateSystem(CoordinateSystemFactory::ENGINEER_COORDINATE_SYSTEM));
		}
		else
		{
			std::cout << "SWITCH COORD SYSTEM: DEFAULT" << endl;
			ctrl->getViewer()->setCoordinateSystem(CoordinateSystemFactory::GetDefaultCoordinateSystem());
		}
	}

	void handleKey_p()
	{
		ctrl->getViewer()->print();
	}

	void handleKey_a()
	{
		ctrl->getViewer()->incrementRotation(0, 10.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_d()
	{
		ctrl->getViewer()->incrementRotation(0, -10.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_w()
	{
		ctrl->getViewer()->walk(0.15f, new TimedInterpolation(300,NULL));
	}

	void handleKey_s()
	{
		ctrl->getViewer()->walk(-0.15f, new TimedInterpolation(300,NULL));
	}

	void handleKey_q()
	{
		ctrl->getViewer()->incrementRotation(2, 5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_e()
	{
		ctrl->getViewer()->incrementRotation(2, -5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_c()
	{
		ctrl->getViewer()->incrementRotation(1, 5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_z()
	{
		ctrl->getViewer()->incrementRotation(1, -5.0f, new TimedInterpolation(300,NULL));
	}

    void handleKey_C()
    {
        ctrl->getViewer()->clear();
    }

    void handleKey_RBracket()
    {
        ctrl->getViewer()->incrementTranslation(new Vector3D(0,0,1));
    }

    void handleKey_LBracket()
    {
        ctrl->getViewer()->incrementTranslation(new Vector3D(0,0,-1));
    }
	
	void handleMouseMotion(MouseMotionEvent * mme)
	{
		Mouse * mouse = ctrl->getMouse();

		if (mouse->isLeftButtonDown()) {
			// rotate camera
			float xChange = (float)(mouse->getCurrentX() - mouse->getPreviousX()) / 2.0f;
			float yChange = (float)(mouse->getCurrentY() - mouse->getPreviousY()) / 2.0f;

			ctrl->getViewer()->incrementRotation(
					Transformable::THETA, -xChange, new TimedInterpolation(100,NULL));
			ctrl->getViewer()->incrementRotation(
					Transformable::PHI, -yChange, new TimedInterpolation(100,NULL));
		}
	}
	
	void handleMouseButtonPressed(MouseButtonDown * mbd)
	{
		cout << "MOUSE DOWN: button=" << mbd->getButton() << endl;
	}

	void handleMouseButtonReleased(MouseButtonUp * mbu)
	{
		cout << "MOUSE UP: button=" << mbu->getButton() << endl;
	}
	
private:

	int _systype;

	static const float ROTATE_CHANGE = 5.0f;
	static const float TRANSLATE_CHANGE = 0.2f;
};


/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	CoordinateSystemDemo * demo = new CoordinateSystemDemo(); 
    return 0;
}

