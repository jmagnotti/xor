#include "BehaviorParser.h"


namespace XOR {


// set the static instance to 0
BehaviorParser* BehaviorParser::_behaviorParser = 0;
char* BehaviorParser::_pathToFile = 0;


/*
 * Protected Constructor
 */
BehaviorParser::BehaviorParser()
{
}


/*
 * Singleton accessor
 */
BehaviorParser* BehaviorParser::GetInstance(char* fileName)
{
	if (_behaviorParser == NULL) {
		_behaviorParser = new BehaviorParser();
	}

	_pathToFile = fileName;

	return _behaviorParser;
}


/* 
 * Parses a .behavior file
 */
vector<Transform*> BehaviorParser::parse()
{
	vector<Transform*> transforms;

	char    buffer[32];
	char    delim = ' ';
	char    index;
	int     counter, strPointer;
	string command[5];

	ifstream fin(_pathToFile);

    if (!fin) {
		cout << "COULD NOT FIND BEHAVIOR FILE" << endl;
    }
	else {
		while (! fin.eof()) {
			// set the char* to null
			memset(buffer, '\0', 1024);

			// clear the string array
			for(int i=0; i<5; i++)
				command[i].clear();

			fin.getline(buffer, 1024);

			cout << buffer << endl;

			counter	= strPointer = 0;
			index	= buffer[0];

			// loop until you find the terminating character
			while(index != '\0' && index != '\n' && counter < 1024 && strPointer < 5) {
				command[strPointer] += index;
				
				counter++;
				index = buffer[counter];

				if (index == ' ') {
					strPointer++;

					// get the next char
					counter++;
					index = buffer[counter];
				}
			}
			
			Transform * transformToPush = TransformFactory::CreateTransform(command);

			if (transformToPush != NULL)
				transforms.push_back(transformToPush);
		}
		fin.close();
	}

	return transforms;
}

}

