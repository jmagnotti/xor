#include "../../gor.h"


using namespace XOR;

/**
 * Shows the simplicity of GOR
 */
int main(int argc, char** argv)
{
    Controller * ctrl = Controller::GetInstance();
    ctrl->defaultConfiguration();

    ctrl->getViewer()->setBackground(Color::CORAL);

    new FramesPerSecondCounter();

    //	 this is what we are using as our model
    String2D * hello = new String2D("Hello World!");

    //	 the controller will detect this is not a "WORLD" object
    //	 and automatically wrap it inside of one (how convenient!)
    ctrl->setModel((Renderable*) hello);
    ctrl->run();

    return 0;
}

