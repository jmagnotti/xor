#include "../../gor.h"


using namespace XOR;

/**
 * Shows the simplicity of GOR
 */
int main(int argc, char** argv)
{
    Controller * ctrl = Controller::GetInstance();
    ctrl->defaultConfiguration();

    //    Timer::GetInstance()->setInterval();

    new FramesPerSecondCounter();
    //new CameraRoller();

    //	 this is what we are using as our model
    String2D * hello = new String2D("Hello World!");
    //    Cube * hello = new Cube(new Point3D(0,0,0), 3.0f, new Paint(Color::JMU_PURPLE, Color::JMU_GOLD, Paint::HEIGHT_BASED));

    //	 the controller will detect this is not a "WORLD" object
    //	 and automatically wrap it inside of one (how convenient!)
    ctrl->setModel((Renderable*) hello);
    ctrl->run();

    return 0;
}

