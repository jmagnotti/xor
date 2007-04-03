#include "../../xor.h"

#include "PhotoAlbum.h"
#include "PhotoKeyboardListener.h"

using namespace XOR;


class PhotoConfig : public XavierConfiguration 
{

public:

    PhotoConfig()
    {}


    EventHandlerFactory * getEventFactory() const
    {
        return InputEventProxyFactory::GetInstance();
    }

    const float * getBackgroundColor()
    {
        return Color::DARK_SLATE_GRAY;
    }

    bool isGLFogEnabled()
    {
        return false;
    }
};


/**
 * Entry point of application
 */
int main(int argc, char * argv[])
{
	Controller * ctrl = Controller::GetInstance(new PhotoConfig());

	ctrl->defaultConfiguration();

	ctrl->getMouse()->setDefaultMouseListener(new DefaultMouseListener());

	PhotoAlbum * album = new PhotoAlbum();

	ctrl->setModel(album);

	PhotoKeyboardListener * pkl = new PhotoKeyboardListener(ctrl, album);

	ctrl->getKeyboard()->addListener(pkl);

	ctrl->run();

	return 0;
}

