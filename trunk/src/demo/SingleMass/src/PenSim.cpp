#include "PenSim.h"

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
 * Run the simulation
 */
void PenSim::Run()
{
	// _sim -> init(label, base, filename);
	// 	
	// 	for(int i = 0; i < _thetas.size(); i++)
	// 	{
	// 		glPushMatrix();
	// 			glBegin();
	// 				glRotate(_thetas[i], 0.0f,0.0f);
	// 				_pendulum->renderObject();
	// 			glEnd();
	// 		glPopMatrix();
	// 	}
	// 	
	// 	Exit();

}

/**
 * Initialize the simulation
 */
void PenSim::init(float penLen, Vector3D* base, char* thetaFile)
{	
	//get theta values
	//_thetas = ThetaReader::read(thetaFile);

	_pendulum = new GLPendulum(penLen, base);

	_world = World::GetInstance(_pendulum);
	
	//bus error here
	Controller::GetInstance()->run();
}