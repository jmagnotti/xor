#include "MazeDriver.h"


/**
 * Constructor for the MazeDriver. Takes care of setting up the controller
 */
MazeDriver::MazeDriver() 
{

    // we need a controller object
    Controller * ctrl = Controller::GetInstance(new XavierConfiguration());

    // initialize the maze
    initializeMaze();

    ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
    ctrl->getMouse()->addListener(new DefaultMouseListener());

	
    // the next step is to move the world so that we are at the starting point
    // of the maze. notice that we are rotating the entire world, so the
    // translation will even effect objects added later, like the Terrain.
    // Also note that we had to invert the starting point to get the desired
    // effect.
	ctrl->getCamera()->getOrientation()->incrementYaw(180);
    //ctrl->getCamera()->addTransform(new Rotation(Rotation::YAW, 180));//(Orientation::THETA, 180);

    // add the world to the controller note that since the world is a
    // renderable no cast is necessary
    ctrl->setModel(new CompiledObject3D(_maze));

    // just to show that we can, let's add a string to the world
    //ctrl->getModel()->addObject("text", new String2D("Enjoy the show"));
//    ctrl->getModel()->addObject("text", new Cube(new Vector3D(0,0,-1), 3.0f, new Paint(Color::YELLOW)));

    // lets add some grass
    //Terrain * grass = new Terrain(new Point3D(0,0,0), _maze->getSize());

	
    //FPS counter 
    //ctrl->setFramesPerSecondCounter(new FramesPerSecondCounter());
    
    // starts the visualization all other actions will be performed by
    // callbacks and listeners
    ctrl->run(); 
}


/**
 * This function uses the MazeParser to parse the file maze1.mz It also calls
 * optimize on the maze to remove the bottom face and generate a display list
 */
void MazeDriver::initializeMaze() 
{ 
    MazeParser * mp = MazeParser::GetInstance("resources/maze1.mz");
    _maze = mp->parse(); 
    //_maze->optimize();

    delete mp;
}


/**
 * The entry point of the program
 */
int main(int argc, char **argv) 
{ 
    new MazeDriver();

    // this never executes, but we want to conform to the ANSI standard
    return 0; 
}

