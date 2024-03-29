#include "PenSim.h"

class PenConfig : public XavierConfiguration {
	
public:	
	
	PenConfig()
	{
		//does nothing until initialized
	}
	
	bool isLightingEnabled()
	{
		return true;
	}
	
	unsigned int getTimerInterval()
	{
		return 30;
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
PenSim * PenSim::GetInstance()
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
    Controller::GetInstance()->CleanUpAndExit();

	if(_sim != NULL) {
		delete _sim;
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
	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
	ctrl->getMouse()->addListener(new DefaultMouseListener());
	 
	//create pendulum
	vector<double> thetaVector;
	ThetaReader::read(thetaFile, thetaVector, ThetaReader::RADIANS);
    for (int i=0; i<thetaVector.size(); i++) {
        cout << thetaVector[i] << endl;
    }
	_pendulum = new GLPendulum(1.0f, new Vector3D(0,0,0), thetaVector, true);
	
	//add the pedulum as a timer listener
	Controller::GetInstance()->getTimer()->addListener(_pendulum);
	 
	//setup the world
	ctrl->setModel(new String2D("Pendulum Test"));
	ctrl->getModel()->addObject("ThetaString", _pendulum->getThetaString());
	ctrl->getModel()->addObject("Pen1", _pendulum);
	
	//set up lighting
	GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat softWhite[] = {0.05f, 0.035f, 0.025f};
	GLfloat lightPos[] = {1.0f, 0.0f, 2.0f, 1.0f};
	
	//enable lighting
	glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, softWhite);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//start the controller
	 ctrl->run();
}
