#include "CDStartState.h"

using namespace XOR;

CDStartState * CDStartState::_state = NULL;
	
CDStartState * CDStartState::GetInstance(CDGrid * grid) {
	if (NULL == _state)
		_state = new CDStartState();

	_state->_grid = grid;

	return _state;
}

void CDStartState::activate() {
	_grid->setVisible(false);
	Controller::GetInstance()->getKeyboard()->addListener(this);	
}

void CDStartState::handleKeyEvent(KeyEvent * ke) {
	if (SDLK_SPACE == ke->getKey()) {
		//unregister ourself then setup for the next state
		Controller::GetInstance()->getKeyboard()->removeListener(this);

		CDFixateState * cdfs = CDFixateState::GetInstance(_grid);
		cdfs->activate();
	}
}
