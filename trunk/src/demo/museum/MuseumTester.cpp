#include "../../xor.h"

#include <iostream>

#include "Museum.h"
#include "DoorExtracter.h"
#include "Room.h"

using namespace std;
using namespace XOR;

/**
 *
 */
int main(int argc, char * argv[])
{
	Controller * ctrl = Controller::GetInstance(
            InputEventHandlerFactory::GetInstance());

	ctrl->defaultConfiguration();

	// this is what we are using as our model
	Museum * museum = new Museum();
    cout << "Before room creation" << endl;
    Room * room = new Room(new RectangularPrism(new Vector3D(0,0,-2), 4,3,10, 
            new Paint(TextureFactory::GetInstance()->createTexture("rustyBlue.bmp"))));

    DoorExtracter::SetDoorHeight(2.0f);
    DoorExtracter::SetDoorWidth(1.0f);

    room->extractDoor(RectangularPrism::FRONT);
    room->extractDoor(RectangularPrism::REAR);
    room->extractDoor(RectangularPrism::RIGHT);
    room->extractDoor(RectangularPrism::LEFT);

	museum->addRoom(room);

	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
	ctrl->getMouse()->addListener(new DefaultMouseListener());

	// the controller will detect this is not a "WORLD" object
	// and automatically wrap it inside of one (how convenient!)
	ctrl->setModel(new CompiledObject3D(museum));
	ctrl->run();
}

