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
		Controller * ctrl = Controller::GetInstance();
	    ctrl->defaultConfiguration();

        // need a cleaner way to do this, override the get instance method or something
        ctrl->removeDefaultKeyboardListener();

        yellowCube = new Cube(new Point3D(-.5f,0.0f,-1.0f), 1.0f, new
                Paint(Color::YELLOW, Paint::HEIGHT_BASED));

        _interpolation = new TimedInterpolation(new LinearInterpolator(), THREE_SECONDS);

        // should use the BoundedRangeModel to get screen coordinates
        up = new Translate(0, 1, 0);
        down = new Translate(0, -1, 0);

        left = new Translate(0, 1, 0);
        right = new Translate(0, -1, 0);

	    ctrl->setModel(this);

        yellowCube->compile();

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
    {
        yellowCube->applyTransform(up, _interpolation);
    }

    void godown()
    {
        yellowCube->applyTransform(down, _interpolation);
    }

    void goright()
    {
        yellowCube->applyTransform(right, _interpolation);
    }

    void goleft()
    {
        yellowCube->applyTransform(left, _interpolation);
    }

    void handleKey_l()
    {
        // starts the chain
        yellowCube->applyTransform(up, _interpolation); 
    }

    void interpolationComplete()
    { 
        switch(++stage) { 
            case 0:       goup();    break; 
            case 1:       godown();  break; 
            case 2:       goright(); break; 
            case 3:       goleft();  break; 
            case default: stage = 0; break;
        }

    }

		
private:

	Cube * yellowCube;
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

