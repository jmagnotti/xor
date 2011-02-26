#include "SessionBuilder.h"

using namespace XOR;

void SessionBuilder::build(const char * xmlFile)
{
	srand(time(NULL));

	parameters = XMLNode::openFileHelper(xmlFile, "SessionParameters");

	fixationDuration = atoi(parameters.getChildNode("Fixation").getAttribute("duration"));
	fixationFile = parameters.getChildNode("Fixation").getAttribute("imageFile");
	sampleDuration = atoi(parameters.getChildNode("SampleDisplay").getAttribute("duration"));
	retentionInterval= atoi(parameters.getChildNode("RetentionInterval").getAttribute("duration"));

	//forcing this to be type==Ratio for now
	choiceFR= atoi(parameters.getChildNode("RetentionInterval").getAttribute("duration"));
	interTrialInterval = atoi(parameters.getChildNode("IntertrialInterval").getAttribute("duration"));
	nTrials = atoi(parameters.getChildNode("StimuliSample").getAttribute("trialCount"));

	trialTypes = parameters.getChildNode("StimuliSample").getChildNode("TrialTypes");
	blockSize = atoi(trialTypes.getAttribute("count"));

	reportingMethod = atoi(parameters.getChildNode("ReportingMethod").getAttribute("type"));

    int NUM_LOCS = 25; // can't use location_1
    for (int i=1; i<NUM_LOCS; i++) { locationPopulation.push_back(i); }


    if (reportingMethod == Session::METHOD_RET_STROOP_CHANGE_NOCHANGE) {
        buildRetrievalStroopSession();
    }
    else if (reportingMethod == Session::METHOD_ENC_STROOP_CHANGE_NOCHANGE) {
        buildEncodingStroopSession();
    }
    else if (reportingMethod == Session::METHOD_RANDLOC_CHOOSE_SAME) {
        buildRandomLocationSession();
    }
    //break this out into another method just to keep this cleaner?
    else {
        vector<Trial*> trials; vector<Trial*> FCtrials;
        vector<Trial*> SDtrials; vector<Trial*> NCFCtrials;
        
        //note that we aren't doing ANY randomization except the pictures/locations.
        //trial type order randomization will come later
        for(int block=0; block< (nTrials/blockSize) / 2; block++) {
            for (int trialType = 0; trialType < 2; trialType++) {
                
                for (int j=0; j<blockSize; j++) {
                
                    //If ReportingMethod == 1, then we need to have "no-change" trials, otherwise, all
                    //trials are "change" trials
                    //if (1 == reportingMethod) {
                    //	if (j >= blockSize / 2 )
                    //			ttype = Trial::NO_CHANGE_TRIAL;
                    //}

                    XMLNode xmlTrialType = trialTypes.getChildNode(j);

                    int sds = atoi(xmlTrialType.getAttribute("sample"));
                    int cds = atoi(xmlTrialType.getAttribute("choice"));
                    
                    //we need to get the stimulus class
                    XMLNode stimulusClass = parameters.getChildNode("StimulusSet").
                                                getChildNodeWithAttribute("StimulusClass", "name", xmlTrialType.getAttribute("stimulusClass"));

                    vector<int> picPopulation;
                    for (int i=0; i<atoi(stimulusClass.getAttribute("count")); i++) { picPopulation.push_back(i); }

                    vector<int> samplePicIDs;
                    Helper::SampleWOReplacement(picPopulation, &samplePicIDs, sds); 

                    vector<int> choicePicIDs;   vector<int> FCchoicePicIDs;
                    vector<int> SDchoicePicIDs; vector<int> NCFCchoicePicIDs;

                    Helper::SampleWOReplacement(samplePicIDs, &choicePicIDs, cds); 
                    //SDchoice should have same as choice
                    for(int i=0; i<cds; i++) { SDchoicePicIDs.push_back(choicePicIDs[i]); }
                    
                    int nExtraSample = 0;
                    if (cds == 1) {
                        FCchoicePicIDs.push_back(choicePicIDs[0]);
                        //we will accomplish this in the for loop later
                        //NCFCchoicePicIDs.push_back(choicePicIDs[0]);

                        //if the sample display size is 4 (i.e., a 4::1 trial), we need
                        //to get two more (4::3), otherwise we just need one more
                        //(N::2).
                        nExtraSample = sds == 4 ? 2 : 1;

                        Helper::FreshSampleWOReplacement(samplePicIDs, &FCchoicePicIDs, choicePicIDs, nExtraSample);

                        //use the same ones for NCFC
                        for(int i=0; i<FCchoicePicIDs.size(); i++) { NCFCchoicePicIDs.push_back(FCchoicePicIDs[i]); }
                    }
                    //just straight copy
                    else { 
                        for(int i=0; i<cds; i++) { FCchoicePicIDs.push_back(choicePicIDs[i]); }
                        for(int i=0; i<cds; i++) { NCFCchoicePicIDs.push_back(choicePicIDs[i]); }
                    }

                    //now we need to randomly grab the locations
                    vector<int> sampleLocations;
                    Helper::SampleWOReplacement(locationPopulation, &sampleLocations, sds);

                    //the choice locations are a subset of the sample locations
                    //we want locations to be consistent between sample/choice, so whichever images were chosen, we need to keep those locations the same
                    vector<int> choiceLocations;   vector<int> FCchoiceLocations;
                    vector<int> SDchoiceLocations; vector<int> NCFCchoiceLocations;

                    for(int i=0; i<cds; i++) {
                        //set the choice location to be the same location as when it was the stimulus
                        choiceLocations.push_back(sampleLocations[Helper::FindInVec(samplePicIDs, choicePicIDs[i])]);
                        SDchoiceLocations.push_back(sampleLocations[Helper::FindInVec(samplePicIDs, SDchoicePicIDs[i])]);
                    }
                    for(int i=0; i < cds+nExtraSample; i++) {
                        FCchoiceLocations.push_back(sampleLocations[Helper::FindInVec(samplePicIDs, FCchoicePicIDs[i])]);
                        NCFCchoiceLocations.push_back(sampleLocations[Helper::FindInVec(samplePicIDs, NCFCchoicePicIDs[i])]);
                    }

                    //we have to add the "changed" item after we settle locations, as the match between
                    //sample and choice is part of the location-finding heuristic
                    if (trialType == Trial::CHANGE_TRIAL) {
                        vector<int> oneMore;
                        Helper::FreshSampleWOReplacement(picPopulation, &oneMore, samplePicIDs, 1);

                        //overwrite id.0 on choice pics
                        choicePicIDs[0]   = oneMore[0];
                        FCchoicePicIDs[0] = oneMore[0];

                        SDchoicePicIDs[0] = oneMore[0];
                        NCFCchoicePicIDs[0] = oneMore[0];

                        //For NC forced-choice and same/different style, there are N-1 changed items on change trials
                        //If cds = 1 or 2 then we are fine, as [0] position is set above
                        //If cds >= 3 then we need to have cds-1 changed items
                        if (cds >= 3 || nExtraSample > 1) {
                            //We want them to match as much as possible. Grab cds+nExtraSample - 1 items, assign cds-1 to SDChoice and all to NCFC choice 
                            //This will ensure that SDchoicePicIDs are always a subset of NCFCchoicePicIDs (proper subset only when cds = 1)
                            vector<int> allButOne;

                            //There is a problem with sampling more from samplePicIDs, because we could actually randomly select the same stimulus as oneMore[0].
                            //We need to combine the OneMore vector with the sample pics to create the stale dataset
                            for(int i=0; i<samplePicIDs.size(); i++)
                                oneMore.push_back(samplePicIDs[i]);

                            Helper::FreshSampleWOReplacement(picPopulation, &allButOne, oneMore, (nExtraSample+cds)-2);
                            //Note that if cds-2 == 0 then this won't execute and SDchoicePicIDs will just have the [0] position filled from above
                            //Note further i+1 because [0] position is filled above
                            for (int i=0; i<cds-2; i++)
                                SDchoicePicIDs[i+1] = allButOne[i];

                            for(int i=0; i < nExtraSample+cds-2; i++)
                                NCFCchoicePicIDs[i+1] = allButOne[i];
                        }
                    }
                    //it's a NO_CHANGE_TRIAL, but FC requires change on every trial, so
                    //make it happen. We can't just do this everytime, as we want the
                    //changed item to be the same as on the matched trial when possible
                    else {
                        vector<int> oneMore;
                        Helper::FreshSampleWOReplacement(picPopulation, &oneMore, samplePicIDs, 1);

                        //overwrite id.0 on choice pics
                        FCchoicePicIDs[0] = oneMore[0];
                        NCFCchoicePicIDs[0] = oneMore[0];

                        //same logic as above for cds >= 3
                        if (cds >= 3 || nExtraSample > 1) {
                            vector<int> fcnc_allButOne;
                            Helper::FreshSampleWOReplacement(picPopulation, &fcnc_allButOne, samplePicIDs, (cds+nExtraSample)-2);
                            for (int i=0; i<fcnc_allButOne.size(); i++) {
                                //cout << "NCFC size: " << NCFCchoicePicIDs.size() << "\ti: " << (i+1) << endl;
                                NCFCchoicePicIDs[i+1] = fcnc_allButOne[i];
                            }
                        }
                    }

                    vector<string> sFiles;

                    vector<string> cFiles;   vector<string> FCcFiles;
                    vector<string> SDcFiles; vector<string> NCFCcFiles;

                    for (int i=0; i<samplePicIDs.size(); i++) {
                        sFiles.push_back(stimulusClass.getChildNode(samplePicIDs[i]).getAttribute("location"));
                    }
                    for (int i=0; i<choicePicIDs.size(); i++) {
                        cFiles.push_back(stimulusClass.getChildNode(choicePicIDs[i]).getAttribute("location"));
                    }
                    for (int i=0; i<FCchoicePicIDs.size(); i++) {
                        FCcFiles.push_back(stimulusClass.getChildNode(FCchoicePicIDs[i]).getAttribute("location"));
                    }
                    for (int i=0; i<NCFCchoicePicIDs.size(); i++) {
                        NCFCcFiles.push_back(stimulusClass.getChildNode(NCFCchoicePicIDs[i]).getAttribute("location"));
                    }
                    for (int i=0; i<SDchoicePicIDs.size(); i++) {
                        SDcFiles.push_back(stimulusClass.getChildNode(SDchoicePicIDs[i]).getAttribute("location"));
                    }

                    trials.push_back(new Trial(trialType, sds, cds,
                                                fixationDuration, sampleDuration, retentionInterval, interTrialInterval,
                                                fixationFile, sFiles, sampleLocations, cFiles, choiceLocations));

                    //reflects changes made to the choice display, all other parameters are equivalent
                    FCtrials.push_back(new Trial(Trial::CHANGE_TRIAL, sds, cds+nExtraSample,
                                                fixationDuration, sampleDuration, retentionInterval, interTrialInterval,
                                                fixationFile, sFiles, sampleLocations, FCcFiles, FCchoiceLocations));

                    //SD and No-Change FC trials
                    SDtrials.push_back(new Trial(trialType, sds, cds,
                                                fixationDuration, sampleDuration, retentionInterval, interTrialInterval,
                                                fixationFile, sFiles, sampleLocations, SDcFiles, SDchoiceLocations));

                    NCFCtrials.push_back(new Trial(Trial::CHANGE_TRIAL, sds, cds+nExtraSample,
                                                fixationDuration, sampleDuration, retentionInterval, interTrialInterval,
                                                fixationFile, sFiles, sampleLocations, NCFCcFiles, NCFCchoiceLocations));
                }
            }
        }

        //we need to use the same seed to ensure STRICT matching
        int seed = time(NULL);

        Helper::Reorder(&trials, seed);
        Helper::Reorder(&FCtrials, seed);

        Helper::Reorder(&SDtrials, seed);
        Helper::Reorder(&NCFCtrials, seed);

        string lbl;
        lbl = "Change/NoChange";
        printSession(lbl, seed, trials);

        lbl = "Forced-Choice";
        printSession(lbl, seed, FCtrials);

        lbl = "Same/Different";
        printSession(lbl, seed, SDtrials);

        lbl = "Forced-Choice_NoChange";
        printSession(lbl, seed, NCFCtrials);
    }
}

void SessionBuilder::buildRandomLocationSession()
{
    vector<Trial*> trials;
    for(int block=0; block < (nTrials/blockSize) ; block++) {
        for (int j=0; j<blockSize; j++) {
            XMLNode xmlTrialType = trialTypes.getChildNode(j);

            int sds = atoi(xmlTrialType.getAttribute("sample"));
            int cds = atoi(xmlTrialType.getAttribute("choice"));

            //cout << "got sds and cds" << endl;
            
            //we need to get the stimulus class
            XMLNode stimulusClass = parameters.getChildNode("StimulusSet").
                                        getChildNodeWithAttribute("StimulusClass", "name", xmlTrialType.getAttribute("stimulusClass"));

            vector<int> picPopulation;
            for (int i=0; i<atoi(stimulusClass.getAttribute("count")); i++) { picPopulation.push_back(i); }

            vector<int> samplePicIDs;
            Helper::SampleWOReplacement(picPopulation, &samplePicIDs, sds); 

            vector<int> oneItem; 
            vector<int> changingItems; 
            vector<int> choicePicIDs; 

            //choose the item that stays the same
            Helper::SampleWOReplacement(samplePicIDs, &oneItem, 1); 

            //choose the new pics from the population
            Helper::FreshSampleWOReplacement(picPopulation, &changingItems, samplePicIDs, cds-1);

            //cout << "got pic ids" << endl;

            //1 unchanged item
            choicePicIDs.push_back(oneItem[0]);

            //get n-1 changed items
            for(int i=0; i<cds-1; i++) { choicePicIDs.push_back(changingItems[i]); }

            //now we need to randomly grab the locations
            vector<int> sampleLocations;
            Helper::SampleWOReplacement(locationPopulation, &sampleLocations, sds);

            //grab fresh locations that weren't used in the sample display
            vector<int> choiceLocations;
            Helper::FreshSampleWOReplacement(locationPopulation, &choiceLocations, sampleLocations, cds);

            //cout << "got locs" << endl;

            vector<string> sFiles; vector<string> cFiles;

            for (int i=0; i<samplePicIDs.size(); i++) { sFiles.push_back(stimulusClass.getChildNode(samplePicIDs[i]).getAttribute("location")); }
            for (int i=0; i<choicePicIDs.size(); i++) { cFiles.push_back(stimulusClass.getChildNode(choicePicIDs[i]).getAttribute("location")); }

            trials.push_back(new Trial(Trial::CHANGE_TRIAL, sds, cds,
                                        fixationDuration, sampleDuration, retentionInterval, interTrialInterval,
                                        fixationFile, sFiles, sampleLocations, cFiles, choiceLocations));

            //cout << "finished trial" << endl;
        }
    }

    int seed = time(NULL);
    Helper::Reorder(&trials, seed);

    string lbl("RandomLocationChooseSame");
    printSession(lbl,  seed, trials);
}

void SessionBuilder::buildRetrievalStroopSession()
{
    vector<Trial*> trials;


    //note that we aren't doing ANY randomization except the pictures/locations.
    //trial type order randomization will come later
    for(int block=0; block < (nTrials/blockSize) / 2 ; block++) {
        for (int trialType = 0; trialType < 2; trialType++) {
            for (int j=0; j<blockSize; j++) {

                XMLNode xmlTrialType = trialTypes.getChildNode(j);

                int sds = atoi(xmlTrialType.getAttribute("sample"));
                int cds = atoi(xmlTrialType.getAttribute("choice"));

                //cout << "cds: " << cds << endl;
                //cout << "sds: " << sds << endl;

                //this actually only impacts the choice display
                int type = atoi(xmlTrialType.getAttribute("interference"));

                XMLNode stimulusClass = parameters.getChildNode("StimulusSet").getChildNodeWithAttribute("StimulusClass", "name", xmlTrialType.getAttribute("stimulusClass"));

                vector<int> picPopulation;
                for (int i=0; i<atoi(stimulusClass.getAttribute("count")); i++) { picPopulation.push_back(i); }

                vector<int> samplePicIDs;
                Helper::SampleWOReplacement(picPopulation, &samplePicIDs, sds); 

                vector<int> choicePicIDs; 
                Helper::SampleWOReplacement(samplePicIDs, &choicePicIDs, cds); 

                //now we need to randomly grab the locations
                vector<int> sampleLocations;
                Helper::SampleWOReplacement(locationPopulation, &sampleLocations, sds);

                vector<int> choiceLocations;  
                //set the choice location to be the same location as when it was the stimulus
                for(int i=0; i<cds; i++) {
                    choiceLocations.push_back(sampleLocations[Helper::FindInVec(samplePicIDs, choicePicIDs[i])]);
                }

                if (trialType == Trial::CHANGE_TRIAL) {
                    vector<int> oneMore;
                    Helper::FreshSampleWOReplacement(picPopulation, &oneMore, samplePicIDs, 1);

                    //overwrite id.0 on choice pics
                    choicePicIDs[0]   = oneMore[0];
                }

                vector<string> sFiles;
                vector<string> cFiles;

                string loc, word, color;
                for (int i=0; i<samplePicIDs.size(); i++) {
                    loc   = stimulusClass.getChildNode(samplePicIDs[i]).getAttribute("location");
                    color = stimulusClass.getChildNode(samplePicIDs[i]).getAttribute("name");
                    sFiles.push_back(loc + color + "-" + color + ".jpg");
                }

                //Baseline, Congruent condition
                if (0 == type) {
                    for (int i=0; i<choicePicIDs.size(); i++) {
                        loc   = stimulusClass.getChildNode(choicePicIDs[i]).getAttribute("location");
                        word = stimulusClass.getChildNode(choicePicIDs[i]).getAttribute("name");
                        color = stimulusClass.getChildNode(choicePicIDs[i]).getAttribute("name");
                        cFiles.push_back(loc + word + "-" + color + ".jpg");
                    }
                }
                //Within (intra) list interference
                else if (1 == type) {
                    //For intra-list interference, we basically need to re-order the words, while keeping the colors the same (except for one item on the change trial). because the locations are randomized, we can just ROT1 on the samplePicIDs. We need to use samplePicIDs because DS==1 can occur
                    for (int i=0; i<choicePicIDs.size(); i++) {
                        loc   = stimulusClass.getChildNode(choicePicIDs[i]).getAttribute("location");

                        word  = stimulusClass.getChildNode(Helper::Rot_1(samplePicIDs, i)).getAttribute("name");

                        color = stimulusClass.getChildNode(choicePicIDs[i]).getAttribute("name");
                        cFiles.push_back(loc + word + "-" + color + ".jpg");
                    }
                }

                //Between (extra) list interference
                else if (2 == type) {
                    //For extra-list interference we need to pick new words not in the sample display, we can use fresh sample without replacement here
                    vector<int> choiceWordIDs;
                    vector<int> usedWords;

                    for(int i=0; i<samplePicIDs.size(); i++) { usedWords.push_back(samplePicIDs[i]); }

                    if (trialType == Trial::CHANGE_TRIAL)
                        usedWords.push_back(choicePicIDs[0]);

                    Helper::FreshSampleWOReplacement(picPopulation, &choiceWordIDs, usedWords, cds);

                    for (int i=0; i<choicePicIDs.size(); i++) {
                        loc   = stimulusClass.getChildNode(choicePicIDs[i]).getAttribute("location");

                        word  = stimulusClass.getChildNode(choiceWordIDs[i]).getAttribute("name");

                        color = stimulusClass.getChildNode(choicePicIDs[i]).getAttribute("name");
                        cFiles.push_back(loc + word + "-" + color + ".jpg");
                    }
                }

                //we need to embed the intereference type into the trial type
                int newTrialType = type * 10 + trialType;

                trials.push_back(new Trial(newTrialType, sds, cds,
                                            fixationDuration, sampleDuration, retentionInterval, interTrialInterval,
                                            fixationFile, sFiles, sampleLocations, cFiles, choiceLocations));
            }
        }
    }

    //we need to use the same seed to ensure STRICT matching
    int seed = time(NULL);

    Helper::Reorder(&trials, seed);
    string lbl("Retrieval Stroop: Change/NoChange");
    printSession(lbl, seed, trials);
}


void SessionBuilder::buildEncodingStroopSession()
{
    cout << "NOT IMPLEMENTED" << endl;
}

void SessionBuilder::printSession(string label, int seed, vector<Trial*> trials)
{
    cout << "<Session label='" << label <<"' id='" << seed
         << "' reportingMethod='" << reportingMethod << "'>" << endl;

    cout << "<Trials count='" << nTrials << "'>" << endl;

    for (int i=0; i<trials.size(); i++) {
        trials[i]->setTrialNumber(i+1);
        trials[i]->toXMLString();
    }

    cout << "</Trials>" << endl;
    cout << "</Session>" << endl;
}


SessionBuilder::SessionBuilder()
{ }


int main(int argc, char * argv[])
{ 
    SessionBuilder * sb = new SessionBuilder();

	if (argc > 1) 
        sb->build(argv[1]);
	else 
		sb->build("session468Short.xml");

	return 0;
}

