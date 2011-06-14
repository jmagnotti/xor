#include "CDITIState.h"

using namespace XOR;

CDITIState * CDITIState::_state = NULL;

CDITIState::CDITIState()
{ 

}

CDITIState * CDITIState::GetInstance(CDGrid * grid) {
	if (NULL == _state)
		_state = new CDITIState();

	_state->_grid = grid;

	return _state;
}

void CDITIState::activate()
{
	_grid->setVisible(false);

	Session * s = Session::GetInstance();

	//always have an ITI, even after the last trial, makes things
	//less jarring 
	//IntervalTimer::GetInstance()->addListener(this, s->getInterTrialInterval(), false);

    SerialPortTimer::GetInstance()->addListener(this);

    ticksRemaining = s->getInterTrialInterval();
}

void CDITIState::handleTick()
{
    ticksRemaining--;

    //cout << ticksRemaining << " ";

    if (ticksRemaining <= 0 ) {
        //cout << endl;

        SerialPortTimer::GetInstance()->removeListener(this);

        bool next = Session::GetInstance()->nextTrial();

        if (!next) { CDClosingState::GetInstance(_grid)->activate(); }
        else {
            CDInitialDisplay * cdid = CDInitialDisplay::GetInstance(_grid);
            cdid->activate();
            //CDFixateState::GetInstance(_grid)->activate();
        }
    }
}

