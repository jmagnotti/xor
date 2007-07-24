#include "../../xor.h"

using namespace XOR;

class FullScreen : public XavierConfiguration 
{
    public:
        FullScreen()
        {}

        Uint32 getVideoFlags()
        {
            return SDL_OPENGL | SDL_FULLSCREEN;
        }

        Dimension2D * getDimension() const
        {
            return new Dimension2D(1920, 1200);
        }
};


class MonkeyHead : public Object3D
{

public:

    Vector3D * getBaseVector()
    {
        return new Vector3D(0,0,0);
    }

    Dimension3D * getDimension()
    {
        return new Dimension3D(1,1,1);
    }

    /**
     * CTOR
     */
    MonkeyHead(Vector3D * pos, Dimension3D * size)
    {
        TextureFactory * tf = TextureFactory::GetInstance();
        _object = new RectangularPrism(pos, size, new Paint(Color::RED,
                    tf->createTexture("monkey.png")));
    }


protected:

    void renderObject()
    {
        _object->render();
    }

private:

    Object3D * _object;
};


int main(int argc, char *argv[])
{
    Controller * ctrl = Controller::GetInstance(new FullScreen());

    ctrl->setModel(new MonkeyHead(new Vector3D(0,0,0), new
                Dimension3D(1,1,1)));

    ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
    ctrl->run();

    return 0;
}

