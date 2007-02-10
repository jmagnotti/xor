#include "../../xor.h"

#include <stdlib.h>

using namespace XOR;
using namespace std;

/**
 * Shows the simplicity of XOR
 */
int main(int argc, char** argv)
{

    // we need a reference to the controller, get it through the static
    // accessor method. This method ensures that all requestors get the same
    // controller object (note: Singleton Pattern).
    Controller * ctrl = Controller::GetInstance();

	ctrl->getKeyboard()->addListener(DefaultKeyboardListener::GetInstance());

    // tell the controller to setup friendly defaults for us. This includes
    // mouse, keyboard, view, and reshape defaults. It also sets up openGL 
    // parameters. To only setup I/O and windowing, pass false to the method,
    // then setup openGL parameters yourself. Check out the documentation for
    // Controller::defaultConfiguration(...) for details about exactly what 
    // gets setup.
    ctrl->defaultConfiguration();

    // We are creating the object as a pointer for greater effecincy
    Quadrilateral3D * hello = new Quadrilateral3D(  new Vector3D(-.25,-.25,-1),
													new Vector3D(.25,-.25,-1),
													new Vector3D(.25,.25,-1),
													new Vector3D(-.25,.25,-1), 
													new Paint());

    // the controller will detect this is not a "WORLD" object
    // and automatically wrap it inside of one (how convenient!)
    ctrl->setModel(hello);

    // this call runs the demo.
    ctrl->run();

    // this return never happens, as clean up is done elsewhere.
    // this means you don't need to delete hello, it's memory will
    // be freed by the Controller
    return 0;
}

