#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Helper.h"

using namespace std;

class Session {

public:

	static Session * GetInstance();

	/**
	 * Returns the initial locations active for the current trial
	 */
	vector<int> getInitialLocations();

	/**
	 * Returns the initial picture IDs active for the current trial
	 */
	vector<int> getInitialPictureIDs();

	/**
	 * Returns the second display locations active for the current trial
	 */
	vector<int> getSecondLocations();

	/**
	 * Returns the second display picture IDs active for the current trial
	 */
	vector<int> getSecondPictureIDs();

	/**
	 * Returns the number of the active trial (used by getLoc and getPic)
	 */
	int getCurrentTrial();

	/**
	 * Increments the trial counter and checks for _currentTrial > _maxTrials)
	 */
	bool nextTrial();

	int getNumberOfTrials();

	int getProbeDelay();

	//printSession(char * filePath)

private:

	Session();
	vector<vector<int> > _initialLocations;
	vector<vector<int> > _initialPictureIDs;

	vector<vector<int> > _secondLocations;
	vector<vector<int> > _secondPictureIDs;

	//vector<int> _trialTypes;

	vector<int> _probeDelays;

	int _currentTrial, _trials;

	static Session * _session;
};

#endif			// SESSION_H

