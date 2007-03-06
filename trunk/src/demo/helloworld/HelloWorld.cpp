#include "../../xor.h"
#include <stdlib.h>


using namespace XOR;

/**
 * Shows the simplicity of XOR
 */
int main(int argc, char ** argv)
{
    // We need a reference to the controller, get it through the static
    // accessor method. This method ensures that all requestors get the same
    // controller object (note: Singleton Pattern).
    Controller * ctrl = Controller::GetInstance(InputEventHandlerFactory::GetInstance());

    // tell the controller to setup friendly defaults for us. This includes
    // mouse, keyboard, view, and reshape defaults. It also sets up openGL 
    // parameters. To only setup I/O and windowing, pass false to the method,
    // then setup openGL parameters yourself. Check out the documentation for
    // Controller::defaultConfiguration(...) for details about exactly what 
    // gets setup.
    ctrl->defaultConfiguration();

    // Add a keyboard listener that has a small set of key handlers
	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
	ctrl->getMouse()->addListener(new DefaultMouseListener());

    //Triangle3D * hello = new Triangle3D(new Vector3D(-.25,-.25,-1), new Vector3D(.25,-.25,-1), new Vector3D(.25,.25,-1));
    NormalPolygon3D * hello = new NormalPolygon3D(new Vector3D(.5,.5,-2.5), 0.5, 10);

	CompiledObject3D * co = new CompiledObject3D(new ExtrudedNormalPolygon3D(hello, 5.0f));
	
    // the controller will detect this is not a "WORLD" object
    // and automatically wrap it inside of one (how convenient!)
    ctrl->setModel(co);

    // this call runs the demo.
    ctrl->run();

    // this return never happens, as clean up is done elsewhere.
    // this means you don't need to delete hello, it's memory will
    // be freed by the Controller
    return 0;
}

