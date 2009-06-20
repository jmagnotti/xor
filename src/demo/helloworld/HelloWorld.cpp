#include "../../xor.h"
#include <stdlib.h>


using namespace XOR;
using namespace std;


/**
 * Shows the simplicity of XOR
 */
int main(int argc, char ** argv)
{
    Controller * ctrl = Controller::GetInstance(new XavierConfiguration());

    // Add a keyboard listener that has a small set of key handlers
	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());

	ctrl->getMouse()->addListener(new DefaultMouseListener());

	Paint * p = new Paint(TextureFactory::GetInstance()->createTexture("aquab.bmp"));
				//new Paint(Color::YELLOW, Paint::WIDTH_BASED));

    Cube * cube = new Cube(new Vector3D(0,0,0), 1.0f,p);

    ctrl->setModel(cube);

    // this call runs the demo.
    ctrl->run();

    // this return never happens, as clean up is done elsewhere.
    // this means you don't need to delete hello, it's memory will
    // be freed by the Controller
    return 0;
}

