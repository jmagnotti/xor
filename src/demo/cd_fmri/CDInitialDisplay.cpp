#include "CDInitialDisplay.h"

using namespace XOR;

CDInitialDisplay * CDInitialDisplay::_state = NULL;

CDInitialDisplay::CDInitialDisplay()
{ }

CDInitialDisplay * CDInitialDisplay::GetInstance(CDGrid * grid) {
	if (NULL == _state)
		_state = new CDInitialDisplay();

	_state->_grid = grid;

	return _state;
}

void CDInitialDisplay::activate()
{
	Session * s = Session::GetInstance();

/**
    vector<string>  files   = s->getSampleStimulusFiles();
    vector<int>     locs    = s->getSampleStimulusLocations();
    for(int i=0; i<files.size(); i++)
        cout << files[i] << ", " << locs[i] << "| \t";
    cout << endl;
*/

	_grid->setVisibleLocations(s->getSampleStimulusLocations());
	_grid->setImageFiles(s->getSampleStimulusFiles());
	_grid->jitter();

    //if (s->getReportingMethod() == Session::CONSTELLATION_CHANGE_NOCHANGE)
    //_grid->rebuildConstellation();

	_grid->setVisible(true);

	//IntervalTimer::GetInstance()->addListener(this, s->getSampleDisplayDuration(), false);

    ticksRemaining = s->getSampleDisplayDuration();

    SerialPortTimer::GetInstance()->addListener(this);
}

void CDInitialDisplay::handleTick()
{
    ticksRemaining--;

    if (ticksRemaining <= 0 ) {
        SerialPortTimer::GetInstance()->removeListener(this);
        CDRetentionInterval * cdri = CDRetentionInterval::GetInstance(_grid);
        cdri->activate();
    }
}
