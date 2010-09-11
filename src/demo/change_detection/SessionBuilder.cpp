#include "SessionBuilder.h"

using namespace XOR;

void SessionBuilder::Build(const char * xmlFile)
{
	srand(time(NULL));

	XMLNode parameters = XMLNode::openFileHelper(xmlFile, "SessionParameters");

	int fixationDuration = atoi(parameters.getChildNode("Fixation").getAttribute("duration"));
	const char * fixationFile = parameters.getChildNode("Fixation").getAttribute("imageFile");
	int sampleDuration = atoi(parameters.getChildNode("SampleDisplay").getAttribute("duration"));
	int retentionInterval= atoi(parameters.getChildNode("RetentionInterval").getAttribute("duration"));

	//forcing this to be type==Ratio for now
	int choiceFR= atoi(parameters.getChildNode("RetentionInterval").getAttribute("duration"));
	int interTrialInterval = atoi(parameters.getChildNode("IntertrialInterval").getAttribute("duration"));
	//cout << "ITI: " << atoi(parameters.getChildNode("IntertrialInterval").getAttribute("duration"));
	int nTrials = atoi(parameters.getChildNode("StimuliSample").getAttribute("trialCount"));

	XMLNode trialTypes = parameters.getChildNode("StimuliSample").getChildNode("TrialTypes");
	int blockSize = atoi(trialTypes.getAttribute("count"));

	int reportingMethod = atoi(parameters.getChildNode("ReportingMethod").getAttribute("type"));

	vector<int> locationPopulation;
	int NUM_LOCS = 25; // can't use location_1
	for (int i=1; i<NUM_LOCS; i++) { locationPopulation.push_back(i); }

	vector<Trial*> trials;
	vector<Trial*> FCtrials;
	
	//note that we aren't doing ANY randomization except the pictures/locations.
	//trial type randomization will come later
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

				vector<int> choicePicIDs;
				vector<int> FCchoicePicIDs;
				Helper::SampleWOReplacement(samplePicIDs, &choicePicIDs, cds); 

				int nExtraSample = 0;
				if (cds == 1) {
					FCchoicePicIDs.push_back(choicePicIDs[0]);

					//if the sample display size is 4 (i.e., a 4::1 trial), we need
					//to get two more (4::3), otherwise we just need one more
					//(N::2).
					nExtraSample = sds == 4 ? 2 : 1;

					Helper::FreshSampleWOReplacement(samplePicIDs, &FCchoicePicIDs, choicePicIDs, nExtraSample);
				}
				//just straight copy
				else { 
					for(int i=0; i<cds; i++) { FCchoicePicIDs.push_back(choicePicIDs[i]); }
				}

				//now we need to randomly grab the locations
				vector<int> sampleLocations;
				Helper::SampleWOReplacement(locationPopulation, &sampleLocations, sds);

				//the choice locations are a subset of the sample locations
				//we want locations to be consistent between sample/choice, so whichever images were chosen, we need to keep those locations the same
				vector<int> choiceLocations;
				vector<int> FCchoiceLocations;
				for(int i=0; i<cds; i++) {
						//set the choice location to be the same location as when it was the stimulus
						choiceLocations.push_back(sampleLocations[Helper::FindInVec(samplePicIDs, choicePicIDs[i])]);
				}
				for(int i=0; i < cds+nExtraSample; i++) {
					FCchoiceLocations.push_back(sampleLocations[Helper::FindInVec(samplePicIDs, FCchoicePicIDs[i])]);
				}

				//we have to add the "changed" item after we settle locations, as the match between
				//sample and choice is part of the location-finding heuristic
				if (trialType == Trial::CHANGE_TRIAL) {
					vector<int> oneMore;
					Helper::FreshSampleWOReplacement(picPopulation, &oneMore, samplePicIDs, 1);

					//overwrite id.0 on choice pics
					choicePicIDs[0] = oneMore[0];
					FCchoicePicIDs[0] = oneMore[0];
				}
				//it's a NO_CHANGE_TRIAL, but FC requires change on every trial, so
				//make it happen. We can't just do this everytime, as we want the
				//changed item to be the same as on the matched trial when possible
				else {
					vector<int> oneMore;
					Helper::FreshSampleWOReplacement(picPopulation, &oneMore, samplePicIDs, 1);

					//overwrite id.0 on choice pics
					FCchoicePicIDs[0] = oneMore[0];
				}

				vector<string> sFiles;
				vector<string> cFiles;
				vector<string> FCcFiles;

				for (int i=0; i<samplePicIDs.size(); i++) {
					sFiles.push_back(stimulusClass.getChildNode(samplePicIDs[i]).getAttribute("location"));
				}
				for (int i=0; i<choicePicIDs.size(); i++) {
					cFiles.push_back(stimulusClass.getChildNode(choicePicIDs[i]).getAttribute("location"));
				}
				for (int i=0; i<FCchoicePicIDs.size(); i++) {
					FCcFiles.push_back(stimulusClass.getChildNode(FCchoicePicIDs[i]).getAttribute("location"));
				}

				trials.push_back(new Trial(trialType, sds, cds,
											fixationDuration, sampleDuration, retentionInterval, interTrialInterval,
											fixationFile, sFiles, sampleLocations, cFiles, choiceLocations));

				//reflects changes made to the choice display, all other parameters are equivalent
				FCtrials.push_back(new Trial(Trial::CHANGE_TRIAL, sds, cds+nExtraSample,
											fixationDuration, sampleDuration, retentionInterval, interTrialInterval,
											fixationFile, sFiles, sampleLocations, FCcFiles, FCchoiceLocations));
			}
		}
	}

	//we need to use the same seed to ensure STRICT matching
	int seed = time(NULL);

	Helper::Reorder(&trials, seed);
	Helper::Reorder(&FCtrials, seed);

	cout << "<Session label='same/different' id='" << seed << "' reportingMethod='" << 1 << "'>" << endl;
	cout << "<Trials count='" << nTrials << "'>" << endl;
	for (int i=0; i<trials.size(); i++) {
		trials[i]->setTrialNumber(i+1);
		trials[i]->toXMLString();
	}
	cout << "</Trials>" << endl;
	cout << "</Session>" << endl;

	cout << "<Session label='forced-choice' id='" << seed << "' reportingMethod='" << 2 << "'>" << endl;
	cout << "<Trials count='" << nTrials << "'>" << endl;
	for (int i=0; i<FCtrials.size(); i++) {
		FCtrials[i]->setTrialNumber(i+1);
		FCtrials[i]->toXMLString();
	}
	cout << "</Trials>" << endl;
	cout << "</Session>" << endl;
}


int main(int argc, char * argv[])
{ 
	//Controller::GetInstance();
	if (argc > 1) 
		SessionBuilder::Build(argv[1]);
	else 
		SessionBuilder::Build("sessionSD.xml");

	return 0;
}

