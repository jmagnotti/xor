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



class CubeDemoConfig : public XavierConfiguration
{
public:

    CubeDemoConfig()
    {}

    EventFactory * getEventFactory()
    {
        return InputEventProxyFactory::GetInstance();
    }

	Uint32 getTimerInterval()
	{
		return 100;
	}
};

/**
 * Demonstrates creation of an InputEventProxyFactory to multicast Keyboard and
 * Mouse events over the wire. Allows uses a Paint with a gradient.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class CubeDemo : public DefaultKeyboardListener
{

public:

    Controller * ctrl;
    Object3D * object3D; 

    void handleKey_0()
    {
        object3D->incrementTranslation(new Vector3D(10, 0, 0), new TimedInterpolation(1000, NULL));
    }


    void handleKey_9()
    {
        object3D->incrementTranslation(new Vector3D(-5, 0, 0), new TimedInterpolation(1000, NULL));
        object3D->incrementRotation(Orientation::PHI, 90, new TimedInterpolation(1000, NULL));
    }


	CubeDemo()
    {
        // the InputEventProxyFactory will send out Keyboard and Mouse events
        // over multicast
		ctrl = Controller::GetInstance(new CubeDemoConfig());
		ctrl->defaultConfiguration();

		ctrl->getMouse()->addListener(new DefaultMouseListener());
		ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
		ctrl->getKeyboard()->addListener(this);

		Paint * p = new Paint(Color::WHITE, Paint::HEIGHT_BASED, TextureFactory::GetInstance()->createTexture("monkey.png")); 
		Cube  * c = new Cube(new Vector3D(-.25, -.25, -4.5), 1.0f, p);
        object3D = new CompiledObject3D(c);
		ctrl->setModel(c);

        // timer tests
        /*
		PrintAllTicks *			pat = new PrintAllTicks();
		PrintOccasionalTicks *	pot = new PrintOccasionalTicks();
		PrintUniqueTick *		put = new PrintUniqueTick();
        */
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

