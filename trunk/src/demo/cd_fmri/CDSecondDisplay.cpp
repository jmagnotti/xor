#include "CDSecondDisplay.h"

using namespace XOR;

CDSecondDisplay * CDSecondDisplay::_state = NULL;

CDSecondDisplay::CDSecondDisplay() 
{ }

CDSecondDisplay * CDSecondDisplay::GetInstance()
{
	if (NULL == _state)
		_state = new CDSecondDisplay();

	return _state;
}


CDSecondDisplay * CDSecondDisplay::GetInstance(CDGrid * grid)
{
	if (NULL == _state)
		_state = new CDSecondDisplay();

	_state->_grid = grid;

	return _state;
}

void CDSecondDisplay::activate()
{
	Session * s = Session::GetInstance();
    SerialPortTimer::GetInstance()->addListener(this);
    //Controller::GetInstance()->getKeyboard()->addListener(this);

/*
	if (s->getReportingMethod() == Session::METHOD_CHANGE_NOCHANGE ||
        s->getReportingMethod() == Session::METHOD_SAME_DIFF ||
        s->getReportingMethod() == Session::METHOD_RET_STROOP_CHANGE_NOCHANGE ||
        s->getReportingMethod() == Session::METHOD_ENC_STROOP_CHANGE_NOCHANGE)
    {
		Controller::GetInstance()->getMouse()->addListener(this);
	}
	else {
		_grid->setMouseListen(true);
	}
*/

    ticksRemaining = s->getDecideDuration();

/**
    vector<string> files = s->getChoiceStimulusFiles();
    vector<int>    locs  = s->getChoiceStimulusLocations();
    for(int i=0; i<files.size(); i++)
        cout << files[i] << ", " << locs[i] << "| \t";
    cout << endl;
*/

    if (s->getReportingMethod() == Session::METHOD_CHOOSE_SAME_LINEUP) {
        vector<int> positions;
        int start   = CDGrid::GetLineUpStartPosition(s->getChoiceDisplaySize());
        int finish  = start + s->getChoiceDisplaySize();
        for(int i=start; i<finish; i++) {
            positions.push_back(i);
        }
        _grid->setVisibleLocations(positions);
    }
    else {
        _grid->setVisibleLocations(s->getChoiceStimulusLocations());
    }

	_grid->setImageFiles(s->getChoiceStimulusFiles());


	//_handled = false;
	_grid->setVisible(true);
	
}

void CDSecondDisplay::handleMouseEvent(MouseEvent * me)
{
	if (! _handled) { 
		if (me->getType() == MouseEvent::MOUSE_BUTTON_DOWN) {

			_handled = true;

			if (Controller::GetInstance()->getMouse()->isLeftButtonDown()) {
				handleChoice(Trial::CHOOSE_CHANGE);
			}
			else {
				handleChoice(Trial::CHOOSE_NO_CHANGE);
			}
		}
	}
}

void CDSecondDisplay::handleKeyEvent(KeyEvent * ke)
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

void CDSecondDisplay::handleChoice(int location)
{
/*
	_reactionTime = Controller::GetInstance()->getTimer()->getElapsedTime() - _reactionTime;
	_grid->setMouseListen(false);

	Session * s = Session::GetInstance();
	s->recordChoice(location, _reactionTime);

	if (s->getReportingMethod() == Session::METHOD_CHANGE_NOCHANGE ||
        s->getReportingMethod() == Session::METHOD_SAME_DIFF ||
        s->getReportingMethod() == Session::METHOD_RET_STROOP_CHANGE_NOCHANGE ||
        s->getReportingMethod() == Session::METHOD_ENC_STROOP_CHANGE_NOCHANGE)
    {
		Controller::GetInstance()->getMouse()->removeListener(this);
		Controller::GetInstance()->getKeyboard()->removeListener(this);
	}

*/
}

void CDSecondDisplay::handleTick()
{
    ticksRemaining--;

    if (ticksRemaining <= 0 ) {
        SerialPortTimer::GetInstance()->removeListener(this);
        CDChoiceState * ccs = CDChoiceState::GetInstance(_grid);
        ccs->activate();
    }

    //cout << "rem: " << ticksRemaining << endl;
}

