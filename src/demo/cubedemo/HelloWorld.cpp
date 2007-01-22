#include "../../xor.h"

using namespace XOR;


class RenderTest : public Renderable, public Positionable
{

public:

    RenderTest()
    {
        setRotation(Positionable::PHI, -20);
        setRotation(Positionable::THETA, 20);
    }

    void render() {
        push();

        glPushMatrix();
        glTranslatef(-.5, -.5f, 0);

        glBegin(GL_QUADS);
            glColor3f(.3, .3, .3); glVertex3f(1,0,0); 
            glColor3f(1,1,1);      glVertex3f(1,1,0);
            glColor3f(1,1,1);      glVertex3f(0,1,0);
            glColor3f(.3,.3,.3);   glVertex3f(0,0,0);

            glColor3f(.3, .3, .3); glVertex3f(1,0,1);
            glColor3f(1,1,1);      glVertex3f(1,1,1);
            glColor3f(1,1,1);      glVertex3f(0,1,1);
            glColor3f(.3, .3, .3); glVertex3f(0,0,1);

            glColor3f(.3, .3, .3); glVertex3f(1,0,1);
            glColor3f(1,1,1);      glVertex3f(1,1,1);
            glColor3f(1,1,1);      glVertex3f(1,1,0);
            glColor3f(.3, .3, .3); glVertex3f(1,0,0);

            glColor3f(.3, .3, .3); glVertex3f(0,0,1);
            glColor3f(1,1,1);      glVertex3f(0,1,1);
            glColor3f(1,1,1);      glVertex3f(0,1,0);
            glColor3f(.3, .3, .3); glVertex3f(0,0,0);

            glColor3f(1,1,1);      glVertex3f(1,1,0);
            glColor3f(1,1,1);      glVertex3f(1,1,1);
            glColor3f(1,1,1);      glVertex3f(0,1,1);
            glColor3f(1,1,1);      glVertex3f(0,1,0);

            glColor3f(.3, .3, .3); glVertex3f(1,0,0);
            glColor3f(.3, .3, .3); glVertex3f(1,0,1);
            glColor3f(.3, .3, .3); glVertex3f(0,0,1);
            glColor3f(.3, .3, .3); glVertex3f(0,0,0);
        glEnd();

        glPopMatrix(); 
        pop();
    }

};


/**
 * Shows the simplicity/brokeness of XOR
 */
int main(int argc, char **argv)
{
    Controller * ctrl = Controller::GetInstance();
    ctrl->defaultConfiguration();

    // slow interval
    /*
    Timer::GetInstance()->setInterval(2000);
    
    Paint * p = new Paint(Color::WHITE, Paint::HEIGHT_BASED);
    p->setAutoGradient(.01);

    Cube * hello = new Cube(new Point3D(0, 0, 0), 1.0f, new Paint(Color::WHITE,
                Paint::HEIGHT_BASED));

    hello->setTranslation(new Dimension3D(-.5,-.5,0));
    hello->setRotation(Positionable::PHI, -20);
    hello->setRotation(Positionable::THETA, 20);
    */
    
    ctrl->setModel(new RenderTest());
    //ctrl->setModel(hello);

    ctrl->run();

    return 0;
}

