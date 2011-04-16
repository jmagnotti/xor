#include "../../xor.h"
#include "Session.h"
#include "Trial.h"

#include "stdio.h"

using namespace XOR;
using namespace std;

string replaceString(string s)
{
    if (s == "images/navy-navy.png")
        return "images/navy.jpg";
    if (s == "images/red-red.png")
        return "images/red.jpg";
    if (s == "images/pink-pink.png")
        return "images/pink.jpg";
    if (s == "images/purple-purple.png")
        return "images/purple.jpg";
    if (s == "images/blue-blue.png")
        return "images/blue.jpg";
    if (s == "images/aqua-aqua.png")
        return "images/aqua.jpg";
    if (s == "images/brown-brown.png")
        return "images/brown.jpg";
    if (s == "images/green-green.png")
        return "images/green.jpg";
    if (s == "images/yellow-yellow.png")
        return "images/yellow.jpg";
    if (s == "images/navy-navy.png")
        return "images/navy.jpg";
    if (s == "images/lime-lime.png")
        return "images/lime.jpg";
    if (s == "images/white-white.png")
        return "images/white.jpg";
    if (s == "images/orange-orange.png")
        return "images/orange.jpg";
    if (s == "images/gray-gray.png")
        return "images/gray.jpg";

    return "ERROR: " + s;
}

int main() {
    Session * s = Session::GetInstance("cncStroopShortTrials.xml", "result.tmp");

    cout << "<Session label='Retrieval Stroop: Change/NoChange' id='" << s->getID() << "' reportingMethod='6'>" << endl;
    cout << "<Trials count='" << s->getNumberOfTrials() << "'>" << endl;

    cout << "\t<Trial trialNumber='" << s->getCurrentTrial() << "' trialType='" << s->getTrialType() << "' sampleDisplaySize='" << s->getSampleDisplaySize() << "' choiceDisplaySize='" << s->getChoiceDisplaySize() << "' fixationDuration='" << s->getFixationDuration() << "' fixationImageFile='images/fixation.jpg' sampleDisplayDuration='1000' retentionInterval='1500' interTrialInterval='2000' >" << endl;
    cout <<"\t\t<sampleStimuli>" << endl;
        vector<string> stimFiles = s->getSampleStimulusFiles(); vector<int> stimLocs = s->getSampleStimulusLocations();
        for(int i=0; i<stimFiles.size(); i++) { cout <<"\t\t\t<stimulus location='" << stimLocs[i] << "' imageFile='"; cout << replaceString(stimFiles[i]); cout << "' />" << endl; }
    cout << "\t\t</sampleStimuli>" << endl;

    cout <<"\t\t<choiceStimuli>" << endl;
        stimFiles = s->getChoiceStimulusFiles(); stimLocs = s->getChoiceStimulusLocations();
        for(int i=0; i<stimFiles.size(); i++) { cout <<"\t\t\t<stimulus location='" << stimLocs[i] << "' imageFile='"; cout << (stimFiles[i]); cout << "' />" << endl; }
    cout << "\t\t</choiceStimuli>" << endl;
    cout << "\t</trial>" << endl;

    while (s->nextTrial()) {
        cout << "\t<Trial trialNumber='" << s->getCurrentTrial() << "' trialType='" << s->getTrialType() << "' sampleDisplaySize='" << s->getSampleDisplaySize() << "' choiceDisplaySize='" << s->getChoiceDisplaySize() << "' fixationDuration='" << s->getFixationDuration() << "' fixationImageFile='images/fixation.jpg' sampleDisplayDuration='1000' retentionInterval='1500' interTrialInterval='2000' >" << endl;
        cout <<"\t\t<sampleStimuli>" << endl;
            stimFiles = s->getSampleStimulusFiles(); vector<int> stimLocs = s->getSampleStimulusLocations();
            for(int i=0; i<stimFiles.size(); i++) { cout <<"\t\t\t<stimulus location='" << stimLocs[i] << "' imageFile='"; cout << replaceString(stimFiles[i]); cout << "' />" << endl; }
        cout << "\t\t</sampleStimuli>" << endl;

        cout <<"\t\t<choiceStimuli>" << endl;
            stimFiles = s->getChoiceStimulusFiles(); stimLocs = s->getChoiceStimulusLocations();
            for(int i=0; i<stimFiles.size(); i++) { cout <<"\t\t\t<stimulus location='" << stimLocs[i] << "' imageFile='"; cout << (stimFiles[i]); cout << "' />" << endl; }
        cout << "\t\t</choiceStimuli>" << endl;

        cout << "\t</trial>" << endl;
    }

    cout << "</trials>" << endl;
    cout << "</Session>" << endl;

    return 0;
}

