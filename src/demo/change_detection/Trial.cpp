#include "Trial.h"

const int Trial::NO_CHANGE_TRIAL = 0;
const int Trial::CHANGE_TRIAL = 1;

const int Trial::CHOOSE_CHANGE = -1;
const int Trial::CHOOSE_NO_CHANGE = -2;

Trial::Trial()
{}

void Trial::recordChoice(string outputFile, int location, int responseTime)
{
	ofstream fout;
	fout.open(outputFile.c_str(), ios::app);
	fout 	<< "\t<Trial trialNumber='" << _trialNumber << "' trialType='" << _trialType << "' "
			<< "trialLabel='" << (_trialType==CHANGE_TRIAL? "change" : "no-change") << "' "

			//--newly aded for response encoding
			<< "choiceLocation='" << location << "' "
			<< "responseTime='" << responseTime << "' "
			<< "choiceLabel='" << (location==CHOOSE_CHANGE? "change" : "no-change") << "' "
			//--

			<< "sampleDisplaySize='" << _sampleDisplaySize << "' "
			<< "choiceDisplaySize='" << _choiceDisplaySize << "' "
			<< "fixationDuration='" << _fixationDuration << "' "
			<< "fixationImageFile='" << _fixationImageFile << "' "
			<< "sampleDisplayDuration='" << _sampleDisplayDuration << "' "
			<< "retentionInterval='" << _retentionInterval << "' "
			<< "interTrialInterval='" << _interTrialInterval << "' "
			<< ">" << endl;
	
	fout << "\t\t<sampleStimuli>" << endl;
	for(int i=0; i<_sampleStimulusLocations.size(); i++) {
		fout << "\t\t\t<stimulus location='" << _sampleStimulusLocations[i] << "' "
				 		   << "imageFile='" << _sampleStimulusFiles[i] << "' />" << endl;
	}
	fout << "\t\t</sampleStimuli>" << endl;

	fout << "\t\t<choiceStimuli>" << endl;
	for(int i=0; i<_choiceStimulusLocations.size(); i++) {
		fout << "\t\t\t<stimulus location='" << _choiceStimulusLocations[i] << "' "
				 		   << "imageFile='" << _choiceStimulusFiles[i] << "' />" << endl;
	}
	fout << "\t\t</choiceStimuli>" << endl;

	fout << "\t</Trial>" << endl;

	fout.close();
}

Trial::Trial(XMLNode trialNode)
{
	_trialNumber = atoi(trialNode.getAttribute("trialNumber"));
	_trialType = atoi(trialNode.getAttribute("trialType"));

	_sampleDisplaySize = atoi(trialNode.getAttribute("sampleDisplaySize"));
	_choiceDisplaySize = atoi(trialNode.getAttribute("choiceDisplaySize"));

	_fixationDuration = atoi(trialNode.getAttribute("fixationDuration"));
	_fixationImageFile = string(trialNode.getAttribute("fixationImageFile"));

	_sampleDisplayDuration = atoi(trialNode.getAttribute("sampleDisplayDuration"));

	_retentionInterval = atoi(trialNode.getAttribute("retentionInterval"));
	_interTrialInterval = atoi(trialNode.getAttribute("interTrialInterval"));

	XMLNode sampleStimuli = trialNode.getChildNode("sampleStimuli");
	for(int i=0; i<_sampleDisplaySize; i++) {
		_sampleStimulusLocations.push_back(atoi(sampleStimuli.getChildNode(i).getAttribute("location")));
		_sampleStimulusFiles.push_back(string(sampleStimuli.getChildNode(i).getAttribute("imageFile")));
	}

	XMLNode choiceStimuli = trialNode.getChildNode("choiceStimuli");
	for(int i=0; i<_choiceDisplaySize; i++) {
		_choiceStimulusLocations.push_back(atoi(choiceStimuli.getChildNode(i).getAttribute("location")));
		_choiceStimulusFiles.push_back(string(choiceStimuli.getChildNode(i).getAttribute("imageFile")));
	}
}


Trial::Trial(int ttype, int sds, int cds, int fd, int sdd, int retIntv, int iti, string fixationImageFile, vector<string> sFiles, vector<int> sLocs, vector<string> cFiles, vector<int> cLocs)
{
	_trialType = ttype;
	_sampleDisplaySize = sds;
	_choiceDisplaySize = cds;
	_fixationDuration = fd;
	_sampleDisplayDuration = sdd;
	_retentionInterval = retIntv;
	_interTrialInterval = iti;

	_fixationImageFile = fixationImageFile;

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
	cout 	<< "\t<Trial trialNumber='" << _trialNumber << "' trialType='" << _trialType << "' "
			<< "sampleDisplaySize='" << _sampleDisplaySize << "' "
			<< "choiceDisplaySize='" << _choiceDisplaySize << "' "
			<< "fixationDuration='" << _fixationDuration << "' "
			<< "fixationImageFile='" << _fixationImageFile << "' "
			<< "sampleDisplayDuration='" << _sampleDisplayDuration << "' "
			<< "retentionInterval='" << _retentionInterval << "' "
			<< "interTrialInterval='" << _interTrialInterval << "' "
			<< ">" << endl;
	
	cout << "\t\t<sampleStimuli>" << endl;
	for(int i=0; i<_sampleStimulusLocations.size(); i++) {
		cout << "\t\t\t<stimulus location='" << _sampleStimulusLocations[i] << "' "
				 		   << "imageFile='" << _sampleStimulusFiles[i] << "' />" << endl;
	}
	cout << "\t\t</sampleStimuli>" << endl;

	cout << "\t\t<choiceStimuli>" << endl;
	for(int i=0; i<_choiceStimulusLocations.size(); i++) {
		cout << "\t\t\t<stimulus location='" << _choiceStimulusLocations[i] << "' "
				 		   << "imageFile='" << _choiceStimulusFiles[i] << "' />" << endl;
	}
	cout << "\t\t</choiceStimuli>" << endl;

	cout << "\t</Trial>" << endl;
}

vector<string> Trial::getSampleStimulusFiles()
{
	return _sampleStimulusFiles;
}

vector<string> Trial::getChoiceStimulusFiles()
{
	return _choiceStimulusFiles;
}

vector<int> Trial::getSampleStimulusLocations()
{
	return _sampleStimulusLocations;
}

vector<int> Trial::getChoiceStimulusLocations()
{
	return _choiceStimulusLocations;
}

string Trial::getFixationFile()
{
	return _fixationImageFile;
}

