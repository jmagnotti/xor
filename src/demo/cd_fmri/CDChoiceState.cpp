#include "CDChoiceState.h"

using namespace XOR;

CDChoiceState * CDChoiceState::_state = NULL;

CDChoiceState::CDChoiceState()
{
	Paint * p;
    p = new Paint(TextureFactory::GetInstance()->createTexture("images/choice.png"));

    double x, y;

    x = 1280/2.0;
    y = 1024/2.0;

	_instructions = new Rectangle2D(new Vector2D(x - 48, y - 48), new Vector2D(x + 48, y + 48), p);
}

CDChoiceState * CDChoiceState::GetInstance(CDGrid * grid)
{
	if (NULL == _state)
		_state = new CDChoiceState();

	_state->_grid = grid;

	return _state;
}

void CDChoiceState::activate()
{
	_grid->setVisible(false);

    Controller::GetInstance()->getKeyboard()->addListener(this);

    Session * s = Session::GetInstance();

    SerialPortTimer::GetInstance()->addListener(this);
    
    ticksRemaining = s->getChoiceDuration();

    //show the question mark
    Controller::GetInstance()->getModel()->addObject("choice", _instructions);

	_reactionTime = Controller::GetInstance()->getTimer()->getElapsedTime(); 

    _handled = false;
}

void CDChoiceState::handleTick()
{
    ticksRemaining--;

    if (ticksRemaining <= 0 ) {
        //take care of the "no choice" condition
        if (!_handled) {
            _handled = true;
            handleChoice(-99);
        }

        SerialPortTimer::GetInstance()->removeListener(this);
        CDITIState * citi = CDITIState::GetInstance(_grid);
        citi->activate();

        Controller::GetInstance()->getModel()->removeObject("choice");
    }
}

void CDChoiceState::handleKeyEvent(KeyEvent * ke)
{
    if (! _handled) {
        _handled = true;
        if (ke->getKey() == SDLK_b) {
            handleChoice(Trial::CHOOSE_CHANGE);
        }
        else if (ke->getKey() == SDLK_r){
            handleChoice(Trial::CHOOSE_NO_CHANGE);
        }
    }
}

void CDChoiceState::handleChoice(int location)
{
	_reactionTime = Controller::GetInstance()->getTimer()->getElapsedTime() - _reactionTime;

	Session * s = Session::GetInstance();
	s->recordChoice(location, _reactionTime);

	/*if (s->getReportingMethod() == Session::METHOD_CHANGE_NOCHANGE ||
        s->getReportingMethod() == Session::METHOD_SAME_DIFF ||
        s->getReportingMethod() == Session::METHOD_RET_STROOP_CHANGE_NOCHANGE ||
        s->getReportingMethod() == Session::METHOD_ENC_STROOP_CHANGE_NOCHANGE)
    {
		Controller::GetInstance()->getMouse()->removeListener(this);
		Controller::GetInstance()->getKeyboard()->removeListener(this);
	}
    */

    Controller::GetInstance()->getKeyboard()->removeListener(this);
}

