#include "../../xor.h"

#include "PhotoAlbum.h"
#include "PhotoKeyboardListener.h"

using namespace XOR;


/**
 * Entry point of application
 */
int main(int argc, char * argv[])
{
	Controller * ctrl = Controller::GetInstance(InputEventProxyFactory::GetInstance());

	ctrl->defaultConfiguration();
	ctrl->getMouse()->setDefaultMouseListener(new DefaultMouseListener());
	PhotoAlbum * album = new PhotoAlbum();

	ctrl->setModel(album);

	PhotoKeyboardListener * pkl = new PhotoKeyboardListener(ctrl, album);
	ctrl->getKeyboard()->addListener(pkl);

	ctrl->run();

	return 0;
}

