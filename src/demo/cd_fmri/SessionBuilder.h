#ifndef SESSION_BUILDER_H
#define SESSION_BUILDER_H

#include <vector>
#include <string>
#include "../../xor.h"

#include "Trial.h"
#include "Session.h"
#include "Helper.h"
#include "xmlParser/xmlParser.h"

using namespace XOR;
using namespace std;

class SessionBuilder {

public:

		/**
		 * const char *: Path to XML file to use to build session
		 */
		void build(const char *);
		SessionBuilder();

private:

        void buildRandomLocationSession();
        void buildRetrievalStroopSession();
        void buildEncodingStroopSession();
        void printSession(string fname, string label, int seed, vector<Trial*> trials);

        int fixationDuration, sampleDuration, retentionInterval, decideDuration, choiceDuration, choiceFR,
            interTrialInterval, nTrials, blockSize, reportingMethod;
        const char * fixationFile;

        vector<int> locationPopulation;
        XMLNode parameters, trialTypes;

};

#endif			// SESSION_BUILDER_H

