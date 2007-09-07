#include "Experiment.h"


Experiment::Experiment(Controller * ctrl)
{
	TextureFactory * tf = TextureFactory::GetInstance();
	RectangularPrism * rp = new RectangularPrism(new Vector3D(-15,-4, 4),
			new Dimension3D(30, 20, -500),
			new Paint(tf->createTexture("of_floor3.jpg")));

	Quadrilateral3D *q = rp->removeFace(RectangularPrism::TOP);
	delete q;
	q = rp->removeFace(RectangularPrism::FRONT);
	delete q;

	String2D * str = new String2D(" ", 400, 20);

	str->setFont(BITMAP_FONT_TYPE_HELVETICA_18);

	ctrl->setModel(str); // 2D state has to be pushed before 3D state because of culling?

	ctrl->getModel()->addObject("room", new CompiledObject3D(rp));

	_state = NULL;

	_currentTrial = 0;
	_maxTrials = 50;
}

Experiment::~Experiment()
{
	if (_state != NULL) {
		_state->exitState();
		delete _state;
	}
}

void Experiment::handleKeyEvent(KeyEvent * ke)
{
	if (SDLK_ESCAPE == ke->getKey())
		Controller::GetInstance()->CleanUpAndExit();

	_state->handleKeyEvent(ke);
}

void Experiment::handleMouseEvent(MouseEvent * me)
{
	_state->handleMouseEvent(me);
}

void Experiment::setState(ExperimentalState * state)
{
	if (_state != NULL)
		_state->exitState();

	_state = state;
	_state->enterState();	
}

int Experiment::getCurrentTrial()
{
	return _currentTrial;
}

int Experiment::getNumberOfTrials()
{
	return _maxTrials;
}

void Experiment::incrementTrialCounter()
{
	++_currentTrial;
}

