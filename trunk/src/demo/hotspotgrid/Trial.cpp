#include "Trial.h"

const int Trial::NO_CHANGE_TRIAL = 0;
const int Trial::CHANGE_TRIAL = 1;

Trial::Trial()
{}

Trial::Trial(int ttype, int sds, int cds, int fd, int sdd, int retIntv, int iti, vector<const char*> sFiles, vector<int> sLocs, vector<const char*> cFiles, vector<int> cLocs)
{
	_trialType = ttype;
	_sampleDisplaySize = sds;
	_choiceDisplaySize = cds;
	_fixationDuration = fd;
	_sampleDisplayDuration = sdd;
	_retentionInterval = retIntv;
	_interTrialInterval = iti;

	_sampleStimulusFiles = sFiles;
	_sampleStimulusLocations = sLocs;

	_choiceStimulusFiles = cFiles;
	_choiceStimulusLocations = cLocs;
}

int Trial::getFixationDuration()
{
	return _fixationDuration;
}

int Trial::getSampleDisplayDuration()
{
	return _sampleDisplayDuration;
}

int Trial::getRetentionInterval()
{
	return _retentionInterval;
}

int Trial::getInterTrialInterval()
{
	return _interTrialInterval;
}

int Trial::getChoiceDisplaySize()
{
	return _choiceDisplaySize;
}

int Trial::getSampleDisplaySize()
{
	return _sampleDisplaySize;
}

void Trial::setTrialNumber(int tnum)
{
	_trialNumber = tnum;
}

void Trial::toXMLString()
{
	cout 	<< "<Trial trialNumber='" << _trialNumber << "' trialType='" << _trialType << "' "
			<< "sampleDisplaySize='" << _sampleDisplaySize << "' "
			<< "choiceDisplaySize='" << _choiceDisplaySize << "' "
			<< "fixationDuration='" << _fixationDuration << "' "
			<< "sampleDisplayDuration='" << _sampleDisplayDuration << "' "
			<< "retentionInterval='" << _retentionInterval << "' "
			<< "interTrialInterval='" << _interTrialInterval << "' "
			<< ">" << endl;
	
	cout << "\t<sampleStimuli>" << endl;
	for(int i=0; i<_sampleStimulusLocations.size(); i++) {
		cout << "\t\t<stimulus location='" << _sampleStimulusLocations[i] << "' "
				 		   << "imageFile='" << _sampleStimulusFiles[i] << "' />" << endl;
	}
	cout << "\t</sampleStimuli>" << endl;

	cout << "\t<choiceStimuli>" << endl;
	for(int i=0; i<_choiceStimulusLocations.size(); i++) {
		cout << "\t\t<stimulus location='" << _choiceStimulusLocations[i] << "' "
				 		   << "imageFile='" << _choiceStimulusFiles[i] << "' />" << endl;
	}
	cout << "\t</choiceStimuli>" << endl;

	cout << "</Trial>" << endl;
}

