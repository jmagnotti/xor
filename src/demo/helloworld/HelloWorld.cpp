#include "../../xor.h"
#include <stdlib.h>


using namespace XOR;


class FullScreen : public XavierConfiguration
{
    public:
       
    FullScreen()
    {}

};


class RShape : public Object3D
{
		Dimension3D * getDimension()
		{}

		Vector3D * getBaseVector()
		{}

        void renderObject()
        {
            glBegin(GL_QUADS);
                glVertex3f(0,0,0);
                glVertex3f(1,0,0);
                glVertex3f(1,1,0);
                glVertex3f(0,1,0);
            glEnd();
        }
};
/**
 * Shows the simplicity of XOR
 */
int main(int argc, char ** argv)
{
    Controller * ctrl = Controller::GetInstance(new XavierConfiguration());

    // Add a keyboard listener that has a small set of key handlers
	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());

	ctrl->getMouse()->addListener(new DefaultMouseListener());


    /*
    cout    << "R: " << Color::RED[0] << " " 
            << "G: " << Color::RED[1] << " " 
            << "B: " << Color::RED[2] << endl;

    */
    Cube * cube = new Cube(new Vector3D(0,0,0), 1.0f, new Paint(Color::RED, Paint::HEIGHT_BASED));

    //ctrl->setModel(new RShape());
    ctrl->setModel(cube);

    // this call runs the demo.
    ctrl->run();

    // this return never happens, as clean up is done elsewhere.
    // this means you don't need to delete hello, it's memory will
    // be freed by the Controller
    return 0;
}

