#include "CDClosingState.h"

using namespace XOR;

CDClosingState * CDClosingState::_state = NULL;

CDClosingState::CDClosingState()
{
	_instructions = new Rectangle2D(new Vector2D(100, 100), new Vector2D(1180, 924),
						new Paint(TextureFactory::GetInstance()->createTexture("images/finished.png")));
}

void CDClosingState::activate()
{
	_grid->setVisible(false);
	Session::GetInstance()->closeResultsFile();

	Controller::GetInstance()->getModel()->addObject("goodbye", _instructions);
}

CDClosingState * CDClosingState::GetInstance(CDGrid * grid)
{
	if (NULL == _state)
		_state = new CDClosingState();

	_state->_grid = grid;

	return _state;
}
