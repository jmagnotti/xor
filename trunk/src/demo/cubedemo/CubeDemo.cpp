#include "../../xor.h"

using namespace XOR;

/**
 * Demonstrates creation of an InputEventProxyFactory to multicast Keyboard and
 * Mouse events over the wire. Allows uses a Paint with a gradient.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class CubeDemo
{

public:

	CubeDemo()
	{
		// the InputEventProxyFactory will send out Keyboard and Mouse events
		// over multicast
		Controller * ctrl = Controller::GetInstance(
                InputEventProxyFactory::GetInstance());
		ctrl->defaultConfiguration();

		ctrl->getMouse()->setDefaultMouseListener(new DefaultMouseListener());
		ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());

		Paint * p = new Paint(Color::WHITE, Paint::HEIGHT_BASED); 
		Cube  * c = new Cube(new Vector3D(-.25, -.25, -4.5), 1.0f, p);
		ctrl->setModel(c);
	}

	/**
	 * Tells the Controller to take charge. All interaction is now delegated to
	 * event handlers.
	 */
	void play(void)
	{
		Controller::GetInstance(NULL)->run();
	}

};


/**
 * Entry point of the application. All input parameters are ignored.
 * Although we are ignoring the parameters, the Macintosh linker fails if they
 * are not included in the method signature. This has more to do with the SDL
 * implementation than anything else.
 */
int main(int argc, char **argv)
{
	CubeDemo * demo = new CubeDemo();
	demo->play();

	// required by the ANSI standard
    return 0;
}

