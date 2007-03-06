#include "../../xor.h"

#include "Museum.h"
#include "Room.h"

using namespace std;
using namespace XOR;

/**
 *
 */
int main(int argc, char * argv[])
{
	Controller * ctrl = Controller::GetInstance(InputEventProxyFactory::GetInstance());
	ctrl->defaultConfiguration();

	// this is what we are using as our model
	Museum * museum = new Museum();
	museum->addRoom(new Room(new RectangularPrism(new Vector3D(0,0,0), 1,1,1, new Paint(Color::WHITE, Color::BLACK, Paint::HEIGHT_BASED
						))));

	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
	ctrl->getMouse()->addListener(new DefaultMouseListener());

	// the controller will detect this is not a "WORLD" object
	// and automatically wrap it inside of one (how convenient!)
	ctrl->setModel(museum);
	ctrl->run();
}
