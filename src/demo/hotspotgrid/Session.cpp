#include "Session.h"

Session * Session::_session = NULL;

void printVec(vector<int> a) {
	for (int i=0; i<a.size(); i++)
		cout << "\t" << a[i];

	cout << endl;
}

/*
 * returns the index associated with the given value for the given vector
 * returns -1 if the needle was not in the haystack
 */
int findInVec(vector<int> haystack, int needle)
{
	int ret = -1;

	for(int i=0; i<haystack.size() && ret < 0; i++) {
		if (haystack[i] == needle)
			ret = i;	
	}
	return ret;
}


Session::Session()
{
	srand(time(NULL));
	int NUM_PICS = 18;
	int NUM_LOCS = 25;

	//number of repeated stimuli

	int DISPLAY_SIZE = 6;
	int PROBE_SIZE = 1; //max is DISPLAY_SIZE-1

	_trials = 12;
	_currentTrial = 1;

	vector<int> pics;
	vector<int> locs;

	//no image0
	for(int i=1; i<=NUM_PICS; i++) { pics.push_back(i); }

	//we don't include loc[0] which is the fixation point
	for(int i=1; i<NUM_LOCS; i++) { locs.push_back(i); }


	vector<int> delays;
	vector<int> delayTimes;
	delayTimes.push_back(0);
	delayTimes.push_back(50);
	delayTimes.push_back(200);
	delayTimes.push_back(800);
	delayTimes.push_back(3200);
	delayTimes.push_back(12800);

	//make sure this is clean division
	int blocks = _trials / delayTimes.size();

	//build probe delays
	for (int k=0; k<delayTimes.size(); k++)
		for(int i=0; i<blocks; i++)
			delays.push_back(delayTimes[k]);

	Helper::SampleWOReplacement(delays, &_probeDelays, _trials);

	// build all the trial info
	for(int i=0; i<_trials; i++) {
		//cout << "\nTrial: " << i << endl;
		
		//we need to grab 8 random pictures	
		vector<int> p;
		Helper::SampleWOReplacement(pics, &p, DISPLAY_SIZE);

		//cout << "1st Pics: "; printVec(p);

		//we need to grab 8 random locations
		vector<int> l;
		Helper::SampleWOReplacement(locs, &l, DISPLAY_SIZE);
		
		//cout << "1st Locs: "; printVec(l);

		_initialLocations.push_back(l);
		_initialPictureIDs.push_back(p);

		//for the second display we want to grab one pic for a comparison and two locations,
		//Importantly, the second image mustn't be in the previous display
		vector<int> p2;
		for(int i=0; i<PROBE_SIZE; i++) {
			p2.push_back(p[i]);
		}

		vector<int> p3;
		Helper::FreshSampleWOReplacement(pics, &p3, p, 1);
		p2.push_back(p3[0]);
		
		//we need to save the corresponding location to remain and the
		//one to change
		vector<int> l2;
		for (int i=0; i<= PROBE_SIZE; i++)
			l2.push_back(l[i]);

		//we need to the two pics in the same vec
		//let's be safe in case we later add more stim
		//for(int i=0; i<p3.size(); i++)
		//p2.push_back(p3[i]);

		//cout << "2nd Pics: "; printVec(p2);
		cout << "2nd Locs: "; printVec(l2);

		_secondLocations.push_back(l2);
		_secondPictureIDs.push_back(p2);
	}
}

vector<int> Session::getInitialLocations()
{
	return _initialLocations[_currentTrial-1];
}

vector<int> Session::getInitialPictureIDs()
{
	return _initialPictureIDs[_currentTrial-1];
}

vector<int> Session::getSecondLocations()
{
	return _secondLocations[_currentTrial-1];
}

vector<int> Session::getSecondPictureIDs()
{
	return _secondPictureIDs[_currentTrial-1];
}

int Session::getCurrentTrial()
{
	return _currentTrial;
}

Session * Session::GetInstance()
{
	if (NULL == _session) 
		_session = new Session();

	return _session;
}

bool Session::nextTrial()
{
	_currentTrial++;
	if (_currentTrial > _trials) return false;

	return true;
}

int Session::getNumberOfTrials()
{
	return _trials;
}

int Session::getProbeDelay() 
{
	return _probeDelays[_currentTrial-1];
}

