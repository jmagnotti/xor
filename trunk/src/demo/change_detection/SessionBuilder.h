#ifndef SESSION_BUILDER_H
#define SESSION_BUILDER_H

#include <vector>
#include "../../xor.h"

#include "Trial.h"
#include "Helper.h"
#include "xmlParser/xmlParser.h"

using namespace XOR;
using namespace std;

class SessionBuilder {

public:

		/**
		 * const char *: Path to XML file to use to build session
		 */
		static void Build(const char *);

private:

		SessionBuilder();

};

#endif			// SESSION_BUILDER_H

