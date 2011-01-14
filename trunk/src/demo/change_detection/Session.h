#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Trial.h"
#include "Helper.h"
#include "xmlParser/xmlParser.h"

using namespace std;

class Session {

public:

	static const int METHOD_CHANGE_NOCHANGE;
	static const int METHOD_WHICH_CHANGED;
	static const int METHOD_SAME_DIFF;
	static const int METHOD_CHOOSE_SAME;
	static const int METHOD_RANDLOC_CHOOSE_SAME;

	/**
	 * const char *	: The xml file containing "Trials"
	 * const char *	: The file to store results in
	 * int			: int to put in the session, defaults to 0
	 */
	static Session * GetInstance(const char *, const char *, int id=0);
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


	int getReportingMethod();
	

	/**
	 * Increments the trial counter and checks for _currentTrial > _maxTrials)
	 * The idea here is to mimic how looping through SQL queries works:
	 * while(session.nextTrial()) do...;
	 */
	bool nextTrial();

	/**
	 * Writes closing tag to results file. Should be called after nextTrial ==
	 * false. Isn't done automatically just in case...
	 */
	void closeResultsFile();

	int getNumberOfTrials();

	int getRetentionInterval();

	int getFixationDuration();

	int getSampleDisplayDuration();

	int getInterTrialInterval();

	string getFixationFile();


	/**
	 * Stores the result of a trial, location, RT pair
	 *
	 * int:	location (id, not X,Y) of response
	 * int: response time (i.e., span between second-image display and choice)
	 */
	void recordChoice(int, int);

	//printSession(char * filePath)

	/**
	 * Returns the user-specified session ID, or 0
	 */
	int getID();

private:

	Session();
	Session(const char *, const char *, int);

	vector<int> _probeDelays;

	vector<Trial*> _trials;

	int _currentTrial;
	int _reportingMethod;
	int _id;

	string _outputFile;

	static Session * _session;
};

#endif			// SESSION_H

