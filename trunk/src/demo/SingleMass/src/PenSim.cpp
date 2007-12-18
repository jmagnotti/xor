#include "PenSim.h"

class PenConfig : public XavierConfiguration {
public:	
	
	bool isLightingEnabled()
	{
		return true;
	}
	
	unsigned int getTimerInterval()
	{
		printf("here");
		return 10;
	}
};

/**
 * Singleton Pointer
 */
PenSim * PenSim::_sim = NULL;

/**
 * Default constructor
 */
PenSim::PenSim()
{}

/**
 * Destructor
 */
PenSim::~PenSim()
{
	delete _pendulum;
}

/**
 * Singleton Accessor
 */
PenSim* PenSim::GetInstance()
{
	if(_sim == NULL)
		_sim = new PenSim();
		
	return _sim;
}

/**
 * Clean up and exit the simulation
 */
void PenSim::Exit()
{
	if(_sim != NULL)
	{
		delete _sim;
		delete _pendulum;
		Controller::GetInstance()->CleanUpAndExit();
	}
}

/**
 * Initialize the simulation
 */
void PenSim::init(float penLen, Vector3D* base, char* thetaFile)
{	
	//init controller and set up viewport
	Controller * ctrl = Controller::GetInstance(new PenConfig());
	ctrl->getCamera()->getOrientation()->incrementPosition(new Vector3D(0,0,5));
	ctrl->getCamera()->getOrientation()->incrementPosition(new Vector3D(0,0,0));
	
	//create pendulum
	_pendulum = new GLPendulum(1.0f, new Vector3D(0,0,0), ThetaReader::read(thetaFile));
	Controller::GetInstance()->getTimer()->addListener(_pendulum);
	
	//setup the world
	ctrl->setModel(new String2D("Pendulum Test"));
	ctrl->getModel()->addObject("Pen1", _pendulum);
	ctrl->getModel()->addObject("String1", new String2D("PenTest"));
	
	//start the controller
	ctrl->run();
}