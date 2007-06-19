#include "../../xor.h"
#include <stdlib.h>


using namespace XOR;


class FullScreen : public XavierConfiguration
{
    public:
       
    FullScreen()
    {}

};


/**
 * Shows the simplicity of XOR
 */
int main(int argc, char ** argv)
{
    Controller * ctrl = Controller::GetInstance(new XavierConfiguration());

    // Add a keyboard listener that has a small set of key handlers
	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());

    Cube * cube = new Cube(new Vector3D(0,0,-1), 3.0f, new Paint(Color::WHITE));

    ctrl->setModel(cube);

    // this call runs the demo.
    ctrl->run();

    // this return never happens, as clean up is done elsewhere.
    // this means you don't need to delete hello, it's memory will
    // be freed by the Controller
    return 0;
}

