#include "../../xor.h"


using namespace XOR;

/*
 * Note that by declaring ourselves as a DefaultKeyboardListener 
 * we are automatically added to the keyboard.
 */
class InterpolationDemo : public DefaultKeyboardListener, public Renderable,
    public InterpolationListener
{

public:

    static const int THREE_SECONDS = 5000;

	/* 
  	 * Constructor
 	 */
	InterpolationDemo()
	{
		Controller * ctrl = Controller::GetInstance(InputEventHandlerFactory::GetInstance());
	    ctrl->defaultConfiguration();

        // need a cleaner way to do this, override the get instance method or something
        //ctrl->removeDefaultKeyboardListener();

        yellowCube = new RectangularPrism(new Vector3D(-.5f,0.0f,-1.0f), 1.0f,
                1.0f, 1.0f, new Paint(Color::YELLOW, Paint::HEIGHT_BASED));

        yellowCube->incrementRotation(Orientation::THETA, 20);
        yellowCube->incrementRotation(Orientation::PHI, -40);

	    ctrl->setModel(this);

	    ctrl->run();
	}


    void render()
    {
        yellowCube->render();
    }


protected:

    void handleKey_w()
    {}

    void handleKey_s()
    {}

    void handleKey_r()
    {}

    void handleKey_p()
    {} 

    void goup()
    { }

    void godown()
    { }

    void goright()
    { }

    void goleft()
    { }

    void handleKey_l()
    {
        // starts the chain
    }

    void interpolationComplete()
    { 
        switch(++stage) { 
            case 0:    goup();    break; 
            case 1:    godown();  break; 
            case 2:    goright(); break; 
            case 3:    goleft();  break; 
            default:   stage=0;   break;
        }

    }

		
private:

	RectangularPrism  * yellowCube;
    Transform * left, * right, * up, * down;

    TimedInterpolation * _interpolation;
    int stage;
};


/*
 *  Tester Main
 */
int main(int argc, char **argv)
{
	new InterpolationDemo();

    return 0;
}

