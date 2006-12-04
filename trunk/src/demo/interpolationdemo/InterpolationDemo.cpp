#include "../../xor.h"


/**
 * Tests the interpolation.
 */
//class InterpolationTester : public InterpolatorListener, public TimerListener
//{
//
//
//public: 
//
//    Point3D *start, *end;
//    static const int TEN_SECONDS = 10000;
//    TimedInterpolator * ti; 
//    unsigned int time;
//    
//
//    /*
//     * Constructors
//     */
//    InterpolationTester()
//    {
//    	
//        time    = 0;
//        start   = new Point3D(0, 0, 0);
//        end     = new Point3D(0, 0, 100);
//
//        ti = new TimedInterpolator(start, end, TEN_SECONDS);
//        ti->start();
//        ti->addListener(this);
//
////        cout << ((Point3D*)ti->getCurrentInterpolation())->toString() << endl;
//        Timer::GetInstance()->addListener(this);
//    }
//
//
//    /*
//     * Called by the timer tick
//     */
//    void handleTick()
//    {
//        Point3D * curr = ((Point3D*)ti->getCurrentInterpolation());
//
//        Controller::GetInstance()->getModel()->addRenderable("eh", new Cube(curr, 2, new Paint(Color::RED)));
//
//        time++;
//        if (time > Timer::GetInstance()->getInterval()) {
//            cout << "Current Value:\t" << curr->toString() << endl;
//            cout << "Current Time:\t" << Timer::GetInstance()->getElapsedTime() << endl;
//            time = 0;
//        }
//    }
//
//
//    /*
//     *  Called when the interpolation is finished
//     */
//    void interpolationComplete()
//    {
//        cout << "Finished!" << endl;
//    }
//
//};
//
//	    InterpolationTester * it = new InterpolationTester();
//

class InterpolationDemo : public DefaultKeyboardListener
{
public:

	/* 
 	* Constructor
 	*/
	InterpolationDemo(int argc, char **argv)
	{
		Controller * ctrl = Controller::GetInstance();
	    ctrl->defaultConfiguration(argc, argv);
	    ctrl->getKeyboard()->addListener(this);
	    
		//FPS counter
	    new FramesPerSecondCounter();
	
	    ctrl->setModel(new String2D("Interpolation Test (press 'x' to compile the yellow cube)"));
	    ctrl->getViewer()->getOrientation()->incrementPosition(new Point3D(0,0,10));
	    ctrl->getViewer()->getOrientation()->setFocalPoint(new Point3D(0,0,0));
	    
	    Cube * whiteCube = new Cube(new Point3D(-.5,-.5,-.5), 1, new Paint(Color::WHITE));
	    ctrl->getModel()->addRenderable("white", whiteCube);
	    
	   	ctrl->getModel()->addRenderable("c_blue", new Cube(new Point3D(0,0,5), 1, new Paint(Color::BLUE)));
	    ctrl->getModel()->addRenderable("c_green", new Cube(new Point3D(0,5,0), 1, new Paint(Color::GREEN)));
	    ctrl->getModel()->addRenderable("c_red", new Cube(new Point3D(5,0,0), 1, new Paint(Color::RED)));
	    
	    yellowCube = new Cube(new Point3D(-.5,-.5,-.5), 1, new Paint(Color::YELLOW));
	    ctrl->getModel()->addRenderable("yellow", yellowCube);
	    Orientate * cubePos = yellowCube->getOrientate();
	    cubePos->incrementPosition(new Point3D(3,3,3));
	    
	    ctrl->run();
	}

	void handleKey_x()
	{
		yellowCube->compile();
	}
		
private:

	Cube * yellowCube;
	
};

/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	InterpolationDemo * demo = new InterpolationDemo(argc, argv); 
	delete demo;
    return 0;
}
