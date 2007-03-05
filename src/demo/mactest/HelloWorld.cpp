#include "../../xor.h"

#include "PrintMousePosition.h"
#include "KeyHandler.h"

using namespace XOR;
using namespace std;

/**
 * Shows the simplicity of XOR
 */
int main(int argc, char * argv[])
{
    // We need a reference to the controller, get it through the static
    // accessor method. This method ensures that all requestors get the same
    // controller object (note: Singleton Pattern).
    Controller * ctrl = Controller::GetInstance(InputEventProxyFactory::GetInstance());

    // tell the controller to setup friendly defaults for us. This includes
    // mouse, keyboard, view, and reshape defaults. It also sets up openGL 
    // parameters. To only setup I/O and windowing, pass false to the method,
    // then setup openGL parameters yourself. Check out the documentation for
    // Controller::defaultConfiguration(...) for details about exactly what 
    // gets setup.
    ctrl->defaultConfiguration();

    //DebugViewer * view = new DebugViewer();
    //view->setDebugInterval(5000);
    //Viewer * old_view = ctrl->setViewer(view);

    new KeyHandler(ctrl);
    new PrintMousePosition(ctrl);
    Paint * p = new Paint(Color::RED, Color::BLACK, Paint::HEIGHT_BASED);
    p->setColorFromAlpha(1.0f);

    //Triangle3D * hello = new Triangle3D(new Vector3D(-.25,-.25,-1), new Vector3D(.25,-.25,-1), new Vector3D(.25,.25,-1));
    Object3D * hello = new Cube(new Vector3D(0,.5,0), 0.5, p);
    ctrl->setModel(hello);//new CompiledObject3D(hello));
    // this call runs the demo.
    ctrl->run();

    // this return never happens, as clean up is done elsewhere.
    // this means you don't need to delete hello, it's memory will
    // be freed by the Controller
    return 0;
}

