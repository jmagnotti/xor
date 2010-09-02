#include "Session.h"
#include <cstdlib>

Session * Session::_session = NULL;

Session::Session(const char * xmlFile, const char * outputFile)
{
	XMLNode trials = XMLNode::openFileHelper(xmlFile, "Trials");
	
	for(int i=0; i<atoi(trials.getAttribute("count")); i++) {
		_trials.push_back(new Trial(trials.getChildNode(i)));
	}

	_currentTrial = 1;

	_outputFile = string(outputFile);
}

void Session::recordChoice(int location, int responseTime)
{
	_trials[_currentTrial-1]->recordChoice(_outputFile, location, responseTime);
}

Session::Session()
{}

int Session::getInterTrialInterval()
{
	return _trials[_currentTrial-1]->getInterTrialInterval();
}
vector<int> Session::getSampleStimulusLocations()
{
	return _trials[_currentTrial-1]->getSampleStimulusLocations();
}

vector<string> Session::getSampleStimulusFiles()
{
	return _trials[_currentTrial-1]->getSampleStimulusFiles();
}

vector<int> Session::getChoiceStimulusLocations()
{
	return _trials[_currentTrial-1]->getChoiceStimulusLocations();
}

vector<string> Session::getChoiceStimulusFiles()
{
	return _trials[_currentTrial-1]->getChoiceStimulusFiles();
}

int Session::getCurrentTrial()
{
	return _currentTrial;
}

Session * Session::GetInstance(const char * xmlFile, const char * outputFile)
{
	if (NULL == _session) 
		_session = new Session(xmlFile, outputFile);

	return _session;
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
	if (_currentTrial > _trials.size()) {
		//I like the idea that _currentTrial == _nTrials when the
		//session is over, so let's not let _currentTrial increase
		//without bound
		_currentTrial--;
		return false;
	}

	return true;
}

int Session::getNumberOfTrials()
{
	return _trials.size();
}

int Session::getRetentionInterval() 
{
	return _trials[_currentTrial-1]->getRetentionInterval();
}

int Session::getFixationDuration() 
{
	return _trials[_currentTrial-1]->getFixationDuration();
}

int Session::getSampleDisplayDuration() 
{
	return _trials[_currentTrial-1]->getSampleDisplayDuration();
}

string Session::getFixationFile(){
	return _trials[_currentTrial-1]->getFixationFile();
}

