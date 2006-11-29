#include <stdlib.h>	//THIS MUST BE INCLUDED IN ALL FILES THAT INCLUDE GLUT.H TO QUIET "EXIT() REDEF ERROR"
#include <GL/glut.h>

#include "Controller.h"
#include "String2D.h"
#include "Terrain.h"

#include "Dimension2D.h"

#include "Room.h"
#include "FramesPerSecondCounter.h"
/**
int main(int argc, char * argv[])
{
	Controller * ctrl = Controller::GetInstance();
	ctrl->defaultConfiguration(argc, argv);

	// this is what we are using as our model
	String2D * hello = new String2D("Hello World!");

    FramesPerSecondCounter * f = new FramesPerSecondCounter();
    f->setLabel(hello);

	// the controller will detect this is not a "WORLD" object
	// and automatically wrap it inside of one (how convenient!)
	ctrl->setModel((Renderable*) hello);
	ctrl->run();
}
**/