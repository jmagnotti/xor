#include "../../xor.h"

#include <iostream>

#include "Museum.h"
#include "DoorExtracter.h"
#include "Room.h"


using namespace std;
using namespace XOR;


/*
 *
 */
void loadRooms(Museum * museum)
{
   XMLNode floor = XMLNode::openFileHelper("museum.xml", "museum").getChildNode("floor");

   cout << "Creating " << floor.nChildNode("room") << " rooms" << endl;
           
   Vector3D    * begin  = new Vector3D((char*) floor.getAttribute("origin"));
   Dimension3D * sz     = new Dimension3D((char*) floor.getAttribute("size"));

   Paint       * p      = new Paint(TextureFactory::GetInstance()->createTexture((char*) floor.getAttribute("floor_texture")));
   Paint       * p1     = new Paint(Color::PURPLE);//TextureFactory::GetInstance()->createTexture((char*) floor.getAttribute("ceiling_texture")));


   NoDepthTestQuadrilateral3D * flr = new NoDepthTestQuadrilateral3D(begin, 
           new Vector3D(begin->getX() + sz->getWidth(), begin->getY(), begin->getZ()),
           new Vector3D(begin->getX() + sz->getWidth(), begin->getY(), begin->getZ()+sz->getDepth()),
           new Vector3D(begin->getX(), begin->getY(), begin->getZ()+sz->getDepth()), p, new PointScale(0,1,0), new TextureScale(
            new Vector2D(begin->getX(), begin->getZ()), new Dimension2D(sz->getWidth(), sz->getDepth()), 
                TextureScale::X_AND_Z, TextureScale::TILED)
           );

   museum->addRoom(flr);

   //Vector3D * roomSize = new Vector3D((char*) floor.getChildNode("room").getAttribute("size"));

   NoDepthTestQuadrilateral3D * ceiling = new NoDepthTestQuadrilateral3D(
           new Vector3D(begin->getX(), 6 + begin->getY(), begin->getZ()), 
           new Vector3D(begin->getX() + sz->getWidth(), 6 + begin->getY(), begin->getZ()),
           new Vector3D(begin->getX() + sz->getWidth(), 6 + begin->getY(), begin->getZ() + sz->getDepth()),
           new Vector3D(begin->getX(), 6, begin->getZ()+sz->getDepth()),
           p1, 
           new PointScale(0,1,0), 
           new TextureScale(new Vector2D(begin->getX(), begin->getZ()), new Dimension2D(sz->getWidth(), sz->getDepth()), 
                TextureScale::X_AND_Z, TextureScale::TILED));

   museum->addRoom(ceiling);

   int roomIter = 0;
   XMLNode roomNode; 
   Room * room;

   char * originStr; 
   char * sizeStr;
   Texture * t;
   for (int i=0; i<floor.nChildNode("room"); i++) {

       roomNode = floor.getChildNode("room", &roomIter);

       originStr = (char *)roomNode.getAttribute("origin");
       sizeStr   = (char *)roomNode.getAttribute("size");

       t = TextureFactory::GetInstance()->createTexture(roomNode.getAttribute("texture"));

       room = new Room(new RectangularPrism(new Vector3D(originStr), 
                       new Dimension3D(sizeStr), new Paint(t)));

       room->removeWall(RectangularPrism::TOP);
       room->removeWall(RectangularPrism::BOTTOM);

       room->extractDoor(RectangularPrism::FRONT);
       room->extractDoor(RectangularPrism::REAR);

       room->extractDoor(RectangularPrism::RIGHT);
       room->extractDoor(RectangularPrism::LEFT);

       museum->addRoom(room);
   }
}


class MuseumConfig : public XavierConfiguration
{

public:

    MuseumConfig()
    {}


    Uint32 getVideoFlags()
    {
        return SDL_OPENGL | SDL_FULLSCREEN;
    }

    Dimension2D * getWindowSize() const
    {
        return new Dimension2D(1440, 900);
    }

    unsigned int getTimerInterval()
    {
        return 50;
    }

};


/**
 *
 */
int main(int argc, char * argv[])
{
	Controller * ctrl = Controller::GetInstance(new MuseumConfig());
	ctrl->defaultConfiguration();

    DoorExtracter::SetDoorHeight(2.0f);
    DoorExtracter::SetDoorWidth(1.5f);

	// this is what we are using as our model
	Museum *  museum = new Museum();

    loadRooms(museum);

	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
	ctrl->getMouse()->addListener(new DefaultMouseListener());

	// the controller will detect this is not a "WORLD" object
	// and automatically wrap it inside of one (how convenient!)
	ctrl->setModel(new CompiledObject3D(museum));
	ctrl->run();
}

