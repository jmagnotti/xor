#include <iostream>
#include <fstream>
#include <string>

#include "../../xor.h"

using namespace XOR;
using namespace std;

int main()
{
	ifstream fin(EventRecorderFactory::EVENTS_FILE);

	while (fin)
	{
		char * a = new char[50];
		memset(a, '\0', 50);
		bool motion=false;

		fin >> a; // main type

		if (atoi(a) == EventRecorderFactory::MOUSE_EVENT) {
			string event = "";

			// time
			memset(a, '\0', 50);
			fin >> a; event.append(a); event.append(" ");

			// type
			memset(a, '\0', 50);
			fin >> a;
			if (atoi(a) == MouseEvent::MOUSE_MOTION)
				motion = true;

			event.append(a); event.append(" ");

			// xpos
			memset(a, '\0', 50);
			fin >> a; event.append(a); event.append(" ");

			// ypos
			memset(a, '\0', 50);
			fin >> a; event.append(a); event.append(" ");
		
			// button || relx
			memset(a, '\0', 50);
			fin >> a; event.append(a); event.append(" ");
			
			if(motion) {
				memset(a, '\0', 50);
				fin >> a; event.append(a); event.append(" ");
			}
			
			cout << "|" << event << "|" << endl;
		}
		else  {
			fin >> a; //time
			fin >> a; //type
			fin >> a; //key
			fin >> a; //mods
			cout << "keyboard " << endl;
		}
	}

	return 0;
}

