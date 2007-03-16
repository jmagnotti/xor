#include "../../xor.h"

using namespace XOR;


class PrintAllTicks : public TimerListener
{
public:
	int counter;
	PrintAllTicks() { counter = 0; Controller::GetInstance(NULL)->getTimer()->addListener(this); }
	void handleTick() { cout << "timer tick: " << ++counter << endl; }
};


class PrintOccasionalTicks : public TimerListener
{
public:
	int counter;
	PrintOccasionalTicks() { counter = 0; IntervalTimer::GetInstance()->addRegularListener(this, 1000); }
	void handleTick() { cout << "  occasional tick [" << ++counter << "]" << endl; }
};


class PrintUniqueTick : public TimerListener
{
public:
	PrintUniqueTick() { IntervalTimer::GetInstance()->addCallbackListener(this, 5000); }
	void handleTick() { cout << "    unique tick !!!!!" << endl; }
};




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

    Controller * ctrl;

	CubeDemo()
	{
        // the InputEventProxyFactory will send out Keyboard and Mouse events
        // over multicast
		ctrl = Controller::GetInstance(InputEventProxyFactory::GetInstance());
		ctrl->defaultConfiguration();

		ctrl->getMouse()->addListener(new DefaultMouseListener());
		ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());

		Paint * p = new Paint(Color::WHITE, Paint::HEIGHT_BASED); 
		Cube  * c = new Cube(new Vector3D(-.25, -.25, -4.5), 1.0f, p);
		ctrl->setModel(new CompiledObject3D(c));

		// timer tests
		PrintAllTicks *			pat = new PrintAllTicks();
		PrintOccasionalTicks *	pot = new PrintOccasionalTicks();
		PrintUniqueTick *		put = new PrintUniqueTick();
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
int main(int argc, char *argv[])
{
	CubeDemo * demo = new CubeDemo();
	demo->play();

	// required by the ANSI standard
    return 0;
}

