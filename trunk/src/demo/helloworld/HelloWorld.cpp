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
    // tell the controller to setup friendly defaults for us. This includes
    // mouse, keyboard, view, and reshape defaults. It also sets up openGL 
    // parameters. To only setup I/O and windowing, pass false to the method,
    // then setup openGL parameters yourself. Check out the documentation for
    // Controller::defaultConfiguration(...) for details about exactly what 
    // gets setup.

    Controller * ctrl = Controller::GetInstance(new XavierConfiguration());

    // Add a keyboard listener that has a small set of key handlers
	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
	ctrl->getMouse()->addListener(new DefaultMouseListener());

    //Triangle3D * hello = new Triangle3D(new Vector3D(-.25,-.25,-1), new Vector3D(.25,-.25,-1), new Vector3D(.25,.25,-1));
    NormalPolygon3D * hello = new NormalPolygon3D(new Vector3D(.5,.5,-2.5), 0.5, 4);
    hello->incrementRotation(Orientation::THETA, 90);
	CompiledObject3D * co = new CompiledObject3D(new ExtrudedNormalPolygon3D(hello, 5));
	
    // the controller will detect this is not a "WORLD" object
    // and automatically wrap it inside of one (how convenient!)
    String2D * str  = new String2D("Hello", 200,200);
    //str->increaseFontSize();
    str->setFont(BITMAP_FONT_TYPE_TIMES_ROMAN_24);
    ctrl->setModel(str);
            
            /*new Rectangle2D(new Vector2D(300,300), 
                   new Vector2D(500,500), 
                   new Paint(Color::RED, Color::WHITE, Paint::HEIGHT_BASED)));
                   */

	ctrl->getModel()->addObject("I hate C++", co);


//	ctrl->getModel()->addObject("I still hate C++", str);

    // this call runs the demo.
    ctrl->run();

    // this return never happens, as clean up is done elsewhere.
    // this means you don't need to delete hello, it's memory will
    // be freed by the Controller
    return 0;
}

