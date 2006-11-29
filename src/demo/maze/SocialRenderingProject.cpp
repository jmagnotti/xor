#include <string.h>
#include "SocialRenderingProject.h"


/**
 * This function uses the MazeParser to parse the file maze1.mz
 * It also calls optimize on the maze to remove the bottom face 
 * and generate a display list
 */
void initializeMaze() 
{
	MazeParser * mp = MazeParser::GetInstance("resources/maze1.mz");

	_maze = mp->parse();
	_maze->optimize();

	delete mp;
}


/**
 * The entry point of the program
 * Command line parameters are accepted and passed to GLUT, but
 * are wholly ignored by they GOR Framework	
 */
int main(int argc, char **argv)
{

	// we need a controller object
	Controller * ctrl = Controller::GetInstance();

	// use the default configuration
	ctrl->defaultConfiguration();

	// initialize the maze
	initializeMaze();

	// we want a world object that is created around the maze
	//World * world = World::GetInstance(new Cube(new Point3D(0,0,0), 1.0f, 
	//	new Paint(Color::AQUAMARINE, Paint::LENGTH_BASED)));
	World * world = World::GetInstance(_maze);
	
	// openGL does the Y axis pointing down, let's change that. NOTE: the controller object
	// would have done this for us if we had passed in a non-World Renderable
	//world->setRotation(new Rotate(180, 0, 1, 0));

	// the next step is to move the world so that we are at the starting point of the maze. notice that we
	// are rotating the entire world, so the translation will even effect objects added later, like the Terrain.
	// Also note that we had to invert the starting point to get the desired effect.
	//world->setTranslation(new Translate(_maze->getStartingPoint()->invert()));
	ctrl->getViewer()->getOrientation()->incrementPosition(_maze->getStartingPoint());
	ctrl->getViewer()->getOrientation()->incrementRotation(Orientate::THETA, 180);

	// add the world to the controller
	// note that since the world is a renderable no cast is necessary
	//ctrl->setModel(world);
	
	ctrl->setModel(world);

	// just to show that we can, let's add a string to the world
    //ctrl->getModel()->addRenderable("text", new String2D("Hello World!"));

	// lets add some grass
	Terrain * grass = new Terrain(new Point3D(0,0,0), _maze->getSize());
	ctrl->getModel()->addRenderable("grass", grass);
	
	// camera roller
	new CameraRoller();

    //FPS counter
    new FramesPerSecondCounter();
    
	// starts the visualization
	// all other actions will be performed by callbacks and listeners
	ctrl->run();
	
	//this never executes, but we want to conform to the ANSI standard
	return 0;
}

