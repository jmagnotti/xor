#include "../../xor.h"


using namespace XOR;


class CoordinateSystemDemo : public DefaultKeyboardListener
{

public:

   /* 
  	* Constructor
 	*/
	CoordinateSystemDemo()
	{
		_math = false;

        Controller * ctrl = Controller::GetInstance();
        ctrl->defaultConfiguration();

        ctrl->getKeyboard()->addListener(this);

        ctrl->setModel(new String2D("Coordinate Test (press 'x' to switch axes)"));

        //ctrl->getViewer()->getOrientation()->incrementPosition(new Point3D(0,0,9));
        //ctrl->getViewer()->getOrientation()->setFocalPoint(new Point3D(0,0,0));
        
        ctrl->getModel()->addRenderable("white", new Cube(new Point3D(-.5,-.5,-.5), 1, new Paint(Color::WHITE)));
        ctrl->getModel()->addRenderable("blue", new Cube(new Point3D(0,0,5), 1, new Paint(Color::BLUE)));
        ctrl->getModel()->addRenderable("green", new Cube(new Point3D(0,5,0), 1, new Paint(Color::GREEN)));
        ctrl->getModel()->addRenderable("red", new Cube(new Point3D(5,0,0), 1, new Paint(Color::RED)));

        ctrl->run();
	}

	void handleKey_1()
	{
		Controller::GetInstance()->getViewer()->getOrientation()->setFocalPoint(
				((Cube *)Controller::GetInstance()->getModel()->getRenderable("white"))->getRegistrationPoint());
	}

	void handleKey_x()
	{
		cout << "SWITCH AXES\n";
		_math = !_math;
		Controller::GetInstance()->getViewer()->setCoordinateSystem(_math);
	}
	
private:

	bool _math;
};


/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	CoordinateSystemDemo * demo = new CoordinateSystemDemo(); 
    return 0;
}

