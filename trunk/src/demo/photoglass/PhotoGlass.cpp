#include "PhotoGlass.h"
#include "PictureLoader.h"
#include "GlassKeyListener.h"
#include <string>
#include <iostream>


using namespace XOR;

/**
 * This constructor gets things off the ground.
 */ 

PhotoGlass::PhotoGlass()
{
	ctrl = Controller::GetInstance(new NoFogConfig());
	ctrl->getKeyboard()->addListener(new GlassKeyListener(this));
	ctrl->getMouse()->addListener(new DefaultMouseListener());

	ctrl->setModel(new String2D("PhotoGlass"));

   /* TextureFactory * tf = TextureFactory::GetInstance();
	Paint * p = new Paint(tf->createTexture("monkey.png"));
	Transformable3D * cube  = new Transformable3D(new Cube(new Vector3D(-3, -3, 0), 3, p));

	Object3DCollection * collection = new Object3DCollection();
	ctrl->getModel()->addObject("test", cube);
    */	
	PictureLoader * pl = new FakePictureLoader(25+18);
	pictures = pl->load();	
	_currentpic = pictures[0];
	displayPictures();	
	//Transformable3D * temp = pictures[0]->getTransformable();
//	Action * meh = new MoveAction(cube, new Vector3D(0,-1,0), NULL);
	//temp->addTransform(Translate::CreateTranslate(new 
	//			Vector3D(0,-1,0), 3000, meh));
	/*cube = pictures[0]->getTransformable();
	cube->addTransform(Rotate::CreateRotate (360, Rotate::ROLL,
				3000, new Vector3D(0,0,0)));
	cube->addTransform(Translate::CreateTranslate(new Vector3D(-1,-1,-11), 3000, NULL));
	*/	
	cout << "Attempting to set arrangement..." << endl;
	setArrangement(new WingArrangement());
}

/**
 * changes the selection in the direction passed in.
 * TODO: Change this to use some sweet constants
 * until then:
 * 1 - n 
 * 2 - s
 * 3 - e
 * 4 - w
 *
 * TODO: There seems to be a suspicious problem
 * with north not being north? BAFFLING.
 * For now the key listener has been hacked.
 */
void PhotoGlass::changeSelection(int direction)
{
	Picture * nextpic;
	switch(direction) {
		case 1:
			nextpic = _currentpic->getNorth();
			break;
		case 2:
			nextpic = _currentpic->getSouth();
			break;
		case 3:
			nextpic = _currentpic->getEast();
			break;
		case 4:
			nextpic = _currentpic->getWest();
			break;
		default:
			nextpic = _currentpic;
			break;
	}
	
	_currentpic->undo();
	nextpic->highlight();
	_currentpic = nextpic;
}

/** 
 * Adds all of the pictures to the world
 *
 * TODO: Should proably be part of the Loader
 */
void PhotoGlass::displayPictures()
{
//	Object3DCollection * collection = new Object3DCollection();
	for(int i = 0; i < pictures.size(); i++)
	{
		char buf[10];
		sprintf(buf, "%d", i);
		ctrl->getModel()->addObject(buf, pictures[i]->getTransformable());	
	}
//	_currentpic = pictures[0];
//	_currentpic->highlight();	
}
/**
 * Deletes all of the pictures from the World.
 *
 * TODO: Should probably be part of the Loader
 */
void PhotoGlass::cleanPictures()
{
	for(int i = 0; i < pictures.size(); i++)
	{
		char buf[10];
		sprintf(buf, "%d", i);
		ctrl->getModel()->removeObject(buf);
	}
	pictures.clear();
}

void PhotoGlass::setArrangement(Arrangement * arrangement) 
{
	_arrangement = arrangement;
	_arrangement->arrange(pictures);
}

void PhotoGlass::run()
{
	Controller::GetInstance()->run();
}

int main(int argc, char *argv[])
{
	PhotoGlass * demo = new PhotoGlass();
	demo->run();
	return 0;
}

