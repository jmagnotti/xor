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

        ctrl = Controller::GetInstance(new XavierConfiguration());

		ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
        ctrl->getKeyboard()->addListener(this);
		ctrl->getMouse()->addListener(new DefaultMouseListener());

        ctrl->setModel(new String2D("Coordinate Test (press 'x' to switch axes)"));

		ctrl->getCamera()->getOrientation()->incrementPosition(new Vector3D(10,10,10));
		ctrl->getCamera()->getOrientation()->setFocalPoint(new Vector3D(0,0,0));
        
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
		ctrl->getCamera()->getOrientation()->setFocalPoint(new Vector3D(0,0,0));
	}

	void handleKey_x()
	{
		_systype = (_systype+1)%4;

		if (_systype == 1)
		{
			std::cout << "SWITCH COORD SYSTEM: MATH" << endl;
			ctrl->getCamera()->setCoordinateSystem(CoordinateSystemFactory::GetCoordinateSystem(CoordinateSystemFactory::MATH_COORDINATE_SYSTEM));
		}
		else if (_systype == 2)
		{
			std::cout << "SWITCH COORD SYSTEM: LEFT OPENGL" << endl;
			ctrl->getCamera()->setCoordinateSystem(CoordinateSystemFactory::GetCoordinateSystem(CoordinateSystemFactory::LEFT_OPENGL_COORDINATE_SYSTEM));
		}
		else if (_systype == 3)
		{
			std::cout << "SWITCH COORD SYSTEM: ENGINEER" << endl;
			ctrl->getCamera()->setCoordinateSystem(CoordinateSystemFactory::GetCoordinateSystem(CoordinateSystemFactory::ENGINEER_COORDINATE_SYSTEM));
		}
		else
		{
			std::cout << "SWITCH COORD SYSTEM: DEFAULT" << endl;
			ctrl->getCamera()->setCoordinateSystem(CoordinateSystemFactory::GetDefaultCoordinateSystem());
		}
	}

	void handleKey_c()
	{
		ctrl->getCamera()->getOrientation()->incrementPitch(-5.0f);
	}

	void handleKey_z()
	{
		ctrl->getCamera()->getOrientation()->incrementPitch(5.0f);
	}

    void handleKey_C()
    {
        //ctrl->getCamera()->clear();
    }

    void handleKey_RBracket()
    {
        ctrl->getCamera()->getOrientation()->incrementPosition(new Vector3D(0,0,1));
    }

    void handleKey_LBracket()
    {
        ctrl->getCamera()->getOrientation()->incrementPosition(new Vector3D(0,0,-1));
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

