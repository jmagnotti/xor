#include "../../xor.h"


using namespace XOR;


class CoordinateSystemDemo : public DefaultKeyboardListener, DefaultMouseListener
{

public:

   /* 
  	* Constructor
 	*/
	CoordinateSystemDemo()
	{
		_systype = 0;

        Controller * ctrl = Controller::GetInstance(LocalEventHandlerFactory::GetInstance());
        ctrl->defaultConfiguration();

		ctrl->removeDefaultKeyboardListener();
        ctrl->getKeyboard()->addListener(this);
		ctrl->removeDefaultMouseListener();
		ctrl->getMouse()->addListener(this);

        ctrl->setModel(new String2D("Coordinate Test (press 'x' to switch axes)"));

		ctrl->getViewer()->incrementTranslation(new Dimension3D(10,10,10));
		ctrl->getViewer()->setFocalPoint(new Dimension3D(0,0,0));
        
        ctrl->getModel()->addRenderable("white", new Cube(new Point3D(.5,.5,.5), 1, new Paint(Color::WHITE)));
        ctrl->getModel()->addRenderable("blue", new Cube(new Point3D(0,0,5), 1, new Paint(Color::BLUE)));
        ctrl->getModel()->addRenderable("green", new Cube(new Point3D(0,5,0), 1, new Paint(Color::GREEN)));
        ctrl->getModel()->addRenderable("red", new Cube(new Point3D(5,0,0), 1, new Paint(Color::RED)));

        ctrl->run();
	}

	void handleKey_l()
	{
		cout << "LOOK AT ORIGIN" << endl;
		Controller::GetInstance()->getViewer()->setFocalPoint(new Dimension3D(0,0,0));
	}

	void handleKey_x()
	{
		_systype = (_systype+1)%4;

		if (_systype == 1)
		{
			std::cout << "SWITCH COORD SYSTEM: MATH" << endl;
			Controller::GetInstance()->getViewer()->setCoordinateSystem(CoordinateSystemFactory::GetCoordinateSystem(CoordinateSystemFactory::MATH_COORDINATE_SYSTEM));
		}
		else if (_systype == 2)
		{
			std::cout << "SWITCH COORD SYSTEM: LEFT OPENGL" << endl;
			Controller::GetInstance()->getViewer()->setCoordinateSystem(CoordinateSystemFactory::GetCoordinateSystem(CoordinateSystemFactory::LEFT_OPENGL_COORDINATE_SYSTEM));
		}
		else if (_systype == 3)
		{
			std::cout << "SWITCH COORD SYSTEM: ENGINEER" << endl;
			Controller::GetInstance()->getViewer()->setCoordinateSystem(CoordinateSystemFactory::GetCoordinateSystem(CoordinateSystemFactory::ENGINEER_COORDINATE_SYSTEM));
		}
		else
		{
			std::cout << "SWITCH COORD SYSTEM: DEFAULT" << endl;
			Controller::GetInstance()->getViewer()->setCoordinateSystem(CoordinateSystemFactory::GetDefaultCoordinateSystem());
		}
	}

	void handleKey_p()
	{
		Controller::GetInstance()->getViewer()->printDebugInfo();
	}

	void handleKey_a()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(0, 10.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_d()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(0, -10.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_w()
	{
		Controller::GetInstance()->getViewer()->walk(0.15f, new TimedInterpolation(300,NULL));
	}

	void handleKey_s()
	{
		Controller::GetInstance()->getViewer()->walk(-0.15f, new TimedInterpolation(300,NULL));
	}

	void handleKey_q()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(2, 5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_e()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(2, -5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_c()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(1, 5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_z()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(1, -5.0f, new TimedInterpolation(300,NULL));
	}

    void handleKey_C()
    {
        Controller::GetInstance()->getViewer()->clear();
    }

    void handleKey_RBracket()
    {
        Controller::GetInstance()->getViewer()->incrementTranslation(new Dimension3D(0,0,1));
    }

    void handleKey_LBracket()
    {
        Controller::GetInstance()->getViewer()->incrementTranslation(new Dimension3D(0,0,-1));
    }
	
	void handleMouseMotion(MouseMotionEvent * mme)
	{
		Mouse * mouse = Controller::GetInstance()->getMouse();

		if (mouse->isLeftButtonDown()) {
			// rotate camera
			float xChange = (float)(mouse->getCurrentX() - mouse->getPreviousX()) / 2.0f;
			float yChange = (float)(mouse->getCurrentY() - mouse->getPreviousY()) / 2.0f;

			Controller::GetInstance()->getViewer()->incrementRotation(
					Positionable::THETA, -xChange, new TimedInterpolation(100,NULL));
			Controller::GetInstance()->getViewer()->incrementRotation(
					Positionable::PHI, -yChange, new TimedInterpolation(100,NULL));
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

