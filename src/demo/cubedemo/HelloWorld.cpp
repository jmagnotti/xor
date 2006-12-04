#include "../../xor.h"


using namespace XOR;

/**
 * Shows the simplicity of GOR
 */
int main(int argc, char** argv)
{
    Controller * ctrl = Controller::GetInstance();
    ctrl->defaultConfiguration();
    
    Cube * hello = new Cube(new Point3D(0,0,-3), 3.0f, new Paint(Color::RED, Paint::HEIGHT_BASED));

    new FramesPerSecondCounter();
    
    ctrl->setModel(hello);
    ctrl->run();

    return 0;
}

