#include "../../xor.h"

#include "PhotoAlbum.h"
#include "PhotoKeyboardListener.h"

using namespace XOR;


/**
 * Entry point of application
 */
int main(int argc, char * argv[])
{
//	Controller * ctrl = Controller::GetInstance(FullEventHandlerFactory::GetInstance());
	Controller * ctrl = Controller::GetInstance(InputEventProxyFactory::GetInstance());

	ctrl->defaultConfiguration();
	glDisable(GL_FOG);
	ctrl->getMouse()->setDefaultMouseListener(new DefaultMouseListener());
	PhotoAlbum * album = new PhotoAlbum();

	ctrl->setModel(album);

	PhotoKeyboardListener * pkl = new PhotoKeyboardListener(ctrl, album);
	ctrl->getKeyboard()->addListener(pkl);

	ctrl->run();

	return 0;
}

