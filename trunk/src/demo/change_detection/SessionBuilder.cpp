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

	vector<int> locationPopulation;
	int NUM_LOCS = 25; // can't use location_1
	for (int i=1; i<NUM_LOCS; i++) { locationPopulation.push_back(i); }

	vector<Trial*> trials;
	
	//note that we aren't doing ANY randomization except the pictures/locations.
	//trial type randomization will come later
	for(int block=0; block<nTrials/blockSize; block++) {
		int ttype = Trial::CHANGE_TRIAL;
		for (int j=0; j<blockSize; j++) {
			
			//If ReportingMethod == 1, then we need to have "no-change" trials, otherwise, all
			//trials are "change" trials
			if (1 == atoi(parameters.getChildNode("ReportingMethod").getAttribute("type"))) {
				if (j >= blockSize / 2 )
						ttype = Trial::NO_CHANGE_TRIAL;
			}

			XMLNode trialType = trialTypes.getChildNode(j);

			int sds = atoi(trialType.getAttribute("sample"));
			int cds = atoi(trialType.getAttribute("choice"));
			
			//we need to get the stimulus class
			XMLNode stimulusClass = parameters.getChildNode("StimulusSet").getChildNodeWithAttribute("StimulusClass", "name", trialType.getAttribute("stimulusClass"));

			vector<int> picPopulation;
			for (int i=0; i<atoi(stimulusClass.getAttribute("count")); i++) { picPopulation.push_back(i); }


			vector<int> samplePicIDs;
			Helper::SampleWOReplacement(picPopulation, &samplePicIDs, sds); 

			vector<int> choicePicIDs;
			Helper::SampleWOReplacement(samplePicIDs, &choicePicIDs, cds); 

			//now we need to randomly grab the locations
			vector<int> sampleLocations;
			Helper::SampleWOReplacement(locationPopulation, &sampleLocations, sds);


			//the choice locations are a subset of the sample locations
			//we want locations to be consistent between sample/choice, so whichever images were chosen, we need to keep those locations the same
			vector<int> choiceLocations;
			for(int i=0; i<cds; i++) {
					//set the choice location to be the same location as when it was the stimulus
					choiceLocations.push_back(sampleLocations[Helper::FindInVec(samplePicIDs, choicePicIDs[i])]);
			}

			//we have to add the "changed" item after we settle locations, as the match between
			//sample and choice is part of the location-finding heuristic
			if (ttype == Trial::CHANGE_TRIAL) {
				vector<int> oneMore;
				Helper::FreshSampleWOReplacement(picPopulation, &oneMore, samplePicIDs, 1);

				//overwrite id.0 on choice pics
				choicePicIDs[0] = oneMore[0];
			}

			vector<const char*> sFiles;
			vector<const char*> cFiles;

			for (int i=0; i<samplePicIDs.size(); i++) {
				sFiles.push_back(stimulusClass.getChildNode(samplePicIDs[i]).getAttribute("location"));
			}
			for (int i=0; i<choicePicIDs.size(); i++) {
				cFiles.push_back(stimulusClass.getChildNode(choicePicIDs[i]).getAttribute("location"));
			}

			trials.push_back(new Trial(ttype, sds, cds,
										fixationDuration, sampleDuration, retentionInterval, interTrialInterval,
										fixationFile, sFiles, sampleLocations, cFiles, choiceLocations));
		}
	}

	Helper::Reorder(&trials);

	cout << "<Trials count='" << nTrials << "'>" << endl;
	for (int i=0; i<trials.size(); i++) {
		trials[i]->setTrialNumber(i+1);
		trials[i]->toXMLString();
	}
	cout << "</Trials>" << endl;
}


int main(int argc, char * argv[])
{ 
	//Controller::GetInstance();
	SessionBuilder::Build("session.xml");

	return 0;
}

