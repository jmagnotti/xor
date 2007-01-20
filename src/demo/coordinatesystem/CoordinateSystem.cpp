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

        Controller * ctrl = Controller::GetInstance();
        ctrl->defaultConfiguration();

		// super-special function call
		ctrl->removeDefaultKeyboardListener();
		ctrl->removeDefaultMouseListener();

        //ctrl->getKeyboard()->addListener(this);
		//ctrl->getMouse()->addListener(this);

        ctrl->setModel(new String2D("Coordinate Test (press 'x' to switch axes)"));

		ctrl->getViewer()->incrementTranslation(new Dimension3D(10,10,10));  
		ctrl->getViewer()->setFocalPoint(new Dimension3D(0,0,0));
        //ctrl->getViewer()->incrementPosition(new Point3D(0,0,9));
        
        ctrl->getModel()->addRenderable("white", new Cube(new Point3D(-.5,-.5,-.5), 1, new Paint(Color::WHITE)));
        ctrl->getModel()->addRenderable("blue", new Cube(new Point3D(0,0,5), 1, new Paint(Color::BLUE)));
        ctrl->getModel()->addRenderable("green", new Cube(new Point3D(0,5,0), 1, new Paint(Color::GREEN)));
        ctrl->getModel()->addRenderable("red", new Cube(new Point3D(5,0,0), 1, new Paint(Color::RED)));

        ctrl->run();
	}

	void handleKey_l()
	{
		//Controller::GetInstance()->getViewer()->getOrientation()->setFocalPoint(
		//		((Cube *)Controller::GetInstance()->getModel()->getRenderable("white"))->getRegistrationPoint());
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

	/*
	void handleKey_w()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(Positionable::PHI, ROTATE_CHANGE);
	}

	void handleKey_s()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(Positionable::PHI, 0.0f-(ROTATE_CHANGE));
	}

	void handleKey_a()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(Positionable::THETA, 0.0f-(ROTATE_CHANGE));
	}

	void handleKey_d()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(Positionable::THETA, ROTATE_CHANGE);
	}

	void handleKey_e()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(Positionable::ROLL, 0.0f-(ROTATE_CHANGE));
	}

	void handleKey_q()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(Positionable::ROLL, ROTATE_CHANGE);
	}

	void handleKey_Q()
	{
		Controller::GetInstance()->getViewer()->incrementTranslation(new Dimension3D(TRANSLATE_CHANGE,0,0));
	}

	void handleKey_A()
	{
		Controller::GetInstance()->getViewer()->incrementTranslation(new Dimension3D(0.0f-(TRANSLATE_CHANGE),0,0));
	}

	void handleKey_W()
	{
		Controller::GetInstance()->getViewer()->incrementTranslation(new Dimension3D(0,TRANSLATE_CHANGE,0));
	}

	void handleKey_S()
	{
		Controller::GetInstance()->getViewer()->incrementTranslation(new Dimension3D(0,0.0f-(TRANSLATE_CHANGE),0));
	}

	void handleKey_E()
	{
		Controller::GetInstance()->getViewer()->incrementTranslation(new Dimension3D(0,0,TRANSLATE_CHANGE));
	}

	void handleKey_D()
	{
		Controller::GetInstance()->getViewer()->incrementTranslation(new Dimension3D(0,0,0.0f-(TRANSLATE_CHANGE)));
	}
	*/
	
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

