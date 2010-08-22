#ifndef TRIAL_H
#define TRIAL_H

#include <vector>
#include <iostream>
#include "xmlParser/xmlParser.h"

using namespace std;

class Trial {

public:
		static const int NO_CHANGE_TRIAL;
		static const int CHANGE_TRIAL;
	
	/**
	 * int: trial type, CHANGE_TRIAL or NO_CHANGE_TRIAL
	 * int: sample display size
	 * int: choice display size
	 * int: fixation duration
	 * int: sample display duration
	 * int: retention interval
	 * int: intertrial interval
	 *
	 * vector<const char *>: sample stimulus files
	 * vector<int>: sample stimulus locations
	 * vector<const char *>: choice stimulus files
	 * vector<int>: choice stimulus locations
	 */
	Trial(int, int, int, int, int, int, int, vector<const char *>, vector<int>, vector<const char *>, vector<int>);

	/**
	 * Build the trial object from an xml node. This node should have the same structure as 
	 * the toXMLString function below.
	 */
	Trial(XMLNode trialNode);

	int getFixationDuration();

	int getSampleDisplayDuration();
	int getRetentionInterval();

	int getChoiceDisplayDuration();
	int getInterTrialInterval();

	int getChoiceDisplaySize();
	int getSampleDisplaySize();

	vector<int> getStimulusIDs();
	vector<int> getStimulusLocations();

	/**
	 * Outputs the XML representation for the trial to stdout
	 */
	void toXMLString();

	/**
	 * Only call this if you want to re-order trials. Once a trial has been
	 * completed, it is very bad to change this number. This could be sweet if
	 * you wanted to load up on easy trials or something.
	 */
	void setTrialNumber(int);

private:
	Trial();

	int _sampleDisplaySize, _choiceDisplaySize;
	int _fixationDuration, _sampleDisplayDuration, _retentionInterval, _choiceDisplayDuration, _interTrialInterval;
	int _trialType, _trialNumber;

	vector<const char *> _sampleStimulusFiles;
	vector<const char *> _choiceStimulusFiles;

	vector<int> _sampleStimulusLocations;
	vector<int> _choiceStimulusLocations;
};

#endif			// TRIAL_H

