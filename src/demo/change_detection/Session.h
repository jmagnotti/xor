#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include <string>
#include "Trial.h"
#include "Helper.h"
#include "xmlParser/xmlParser.h"

using namespace std;

class Session {

public:

	/**
	 * const char *: The xml file containing "Trials"
	 * const char *: the file to store results in
	 */
	static Session * GetInstance(const char *, const char *);
	static Session * GetInstance();

	/**
	 * Returns the initial locations active for the current trial
	 */
	vector<int> getSampleStimulusLocations();

	/**
	 * Returns the sample file locations active for the current trial
	 * The file paths are given here, but the textures can be pre-cached by 
	 * using the TextureFactory.CreateTexture method which provides singleton
	 * texture access.
	 */
	vector<string> getSampleStimulusFiles();

	/**
	 * Returns the choice display locations active for the current trial
	 */
	vector<int> getChoiceStimulusLocations();

	/**
	 * Returns the choice file locations active for the current trial
	 * The file paths are given here, but the textures can be pre-cached by 
	 * using the TextureFactory.CreateTexture method which provides singleton
	 * texture access.
	 */
	vector<string> getChoiceStimulusFiles();

	/**
	 * Returns the number of the active trial (used by getLoc and getPic)
	 */
	int getCurrentTrial();

	/**
	 * Increments the trial counter and checks for _currentTrial > _maxTrials)
	 * The idea here is to mimic how looping through SQL queries works:
	 * while(session.nextTrial()) do...;
	 */
	bool nextTrial();

	int getNumberOfTrials();

	int getRetentionInterval();

	int getFixationDuration();

	int getSampleDisplayDuration();

	int getInterTrialInterval();

	string getFixationFile();

	//printSession(char * filePath)

private:

	Session();
	Session(const char *);

	vector<int> _probeDelays;

	vector<Trial*> _trials;

	int _currentTrial;

	static Session * _session;
};

#endif			// SESSION_H

