#include "../../xor.h"

using namespace XOR;

GLuint monkey;

class RenderTest : public Renderable, public Positionable
{

public:

    RenderTest()
    {
        /*
        setRotation(Positionable::PHI, -20);
        setRotation(Positionable::THETA, 20);
        */

        glClearColor(0.0, 0.0, 0.0, 0.0);
        glShadeModel(GL_SMOOTH);

        glEnable(GL_TEXTURE_2D);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        SDL_Surface * tex = NULL;

        tex = IMG_Load("monkey.png");
        if (tex == NULL) {
            cout <<"FAILURE"<<endl;
        }

        /* We shouldn't need to lock it, but whatever */
        if (SDL_MUSTLOCK(tex)) SDL_LockSurface(tex);

        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &monkey);
        glBindTexture(GL_TEXTURE_2D, monkey);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        if (tex->format->BytesPerPixel == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->w, tex->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels);
        else
            cout << "OH NO" << endl;

        if (SDL_MUSTLOCK(tex))
            SDL_UnlockSurface(tex);

        SDL_FreeSurface(tex);
    }

    void render() {
        glClear(GL_COLOR_BUFFER_BIT);

        //push();
        glPushMatrix();
        glTranslatef(-.5, -.5f, 0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, monkey);

        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, monkey);

        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-1.0, -1.0, 0.0);

            glTexCoord2f(1.0, 1.0);
            glVertex3f(1.0, -1.0, 0.0);

            glTexCoord2f(1.0, 0.0);
            glVertex3f(1.0, 1.0, 0.0);

            glTexCoord2f(0.0, 0.0);
            glVertex3f(-1.0, 1.0, 0.0);
        glEnd();

        glDisable(GL_TEXTURE_2D);

/*
        glBegin(GL_QUADS);
            glColor3f(.3, .3, .3); glTexCoord2f(1,0); glVertex3f(1,0,0); 
            glColor3f(1,1,1);      glTexCoord2f(1,1); glVertex3f(1,1,0);
            glColor3f(1,1,1);      glTexCoord2f(0,1); glVertex3f(0,1,0);
            glColor3f(.3,.3,.3);   glTexCoord2f(0,0); glVertex3f(0,0,0);
            glColor3f(.3, .3, .3); glTexCoord2f(1,0); glVertex3f(1,0,1);
            glColor3f(1,1,1);      glTexCoord2f(1,1); glVertex3f(1,1,1);
            glColor3f(1,1,1);      glTexCoord2f(0,1); glVertex3f(0,1,1);
            glColor3f(.3, .3, .3); glTexCoord2f(0,0); glVertex3f(0,0,1);

            glColor3f(.3, .3, .3); glTexCoord2f(1,0); glVertex3f(1,0,1);
            glColor3f(1,1,1);      glTexCoord2f(1,1); glVertex3f(1,1,1);
            glColor3f(1,1,1);      glTexCoord2f(0,1); glVertex3f(1,1,0);
            glColor3f(.3, .3, .3); glTexCoord2f(0,0); glVertex3f(1,0,0);

            glColor3f(.3, .3, .3); glTexCoord2f(1,0); glVertex3f(0,0,1);
            glColor3f(1,1,1);      glTexCoord2f(1,1); glVertex3f(0,1,1);
            glColor3f(1,1,1);      glTexCoord2f(0,1); glVertex3f(0,1,0);
            glColor3f(.3, .3, .3); glTexCoord2f(0,0); glVertex3f(0,0,0);

            glColor3f(1,1,1);      glTexCoord2f(1,0); glVertex3f(1,1,0);
            glColor3f(1,1,1);      glTexCoord2f(1,1); glVertex3f(1,1,1);
            glColor3f(1,1,1);      glTexCoord2f(0,1); glVertex3f(0,1,1);
          glColor3f(1,1,1);      glTexCoord2f(0,0); glVertex3f(0,1,0);

            glColor3f(.3, .3, .3); glTexCoord2f(1,0); glVertex3f(1,0,0);
            glColor3f(.3, .3, .3); glTexCoord2f(1,1); glVertex3f(1,0,1);
            glColor3f(.3, .3, .3); glTexCoord2f(0,1); glVertex3f(0,0,1);
            glColor3f(.3, .3, .3); glTexCoord2f(0,0); glVertex3f(0,0,0);
*/
        glPopMatrix(); 
        //pop();
    }

};


/**
 * Shows the simplicity/brokeness of XOR
 */
int main(int argc, char **argv)
{
    Controller * ctrl = Controller::GetInstance();
    ctrl->defaultConfiguration();

    Texture * t = TextureFactory::GetInstance()->createTexture("monkey.png");

    Paint * p = new Paint(Color::WHITE, Paint::HEIGHT_BASED, t); 
    p->setAutoGradient(.01);

    Cube * hello = new Cube(new Point3D(0, 0, 0), 1.0f, p);
        //new Paint(Color::WHITE, Paint::HEIGHT_BASED));

    hello->setTranslation(new Dimension3D(-.5,-.5,0));
    hello->setRotation(Positionable::PHI, -20);
    hello->setRotation(Positionable::THETA, 20);
    
    //ctrl->setModel(new RenderTest());
    ctrl->setModel(hello);

    ctrl->run();

    return 0;
}

