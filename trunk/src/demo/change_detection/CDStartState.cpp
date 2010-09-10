#include "CDStartState.h"

using namespace XOR;

CDStartState * CDStartState::_state = NULL;

CDStartState::CDStartState()
{
	Paint * p;
	if (Session::GetInstance()->getReportingMethod() == Session::METHOD_CHANGE_NOCHANGE) {
		p = new Paint(TextureFactory::GetInstance()->createTexture("images/instrSD.png"));
	}
	else {
		p = new Paint(TextureFactory::GetInstance()->createTexture("images/instrFC.png"));
	}

	_instructions = new Rectangle2D(new Vector2D(100, 100), new Vector2D(1180, 924), p);
}

CDStartState * CDStartState::GetInstance(CDGrid * grid)
{
	if (NULL == _state)
		_state = new CDStartState();

	_state->_grid = grid;

	return _state;
}

void CDStartState::activate()
{
	_grid->setVisible(false);
	Controller::GetInstance()->getMouse()->addListener(this);

	//show display some text here about what to do
	Controller::GetInstance()->getModel()->addObject("instructions", _instructions);
}

void CDStartState::handleMouseEvent(MouseEvent * me)
{
	if (me->getType() == MouseEvent::MOUSE_BUTTON_DOWN) {
		//unregister ourself then setup for the next state
		Controller::GetInstance()->getKeyboard()->removeListener(this);

		World::GetInstance()->removeObject("instructions");

		DelayedAction * da = new DelayedAction(new StartFixation(_grid), 3000);
		da->execute();
		
	}
}


StartFixation::StartFixation(CDGrid * grid)
{
	_grid = grid;
}	

void StartFixation::execute()
{ 
	CDFixateState * cdfs = CDFixateState::GetInstance(_grid);
	cdfs->activate();
}

