#include "../../xor.h"
#include "DistanceEstimation.cpp"
#include <stdio.h>

using namespace XOR;

int main()
{
	//get rid of an existing events file
	remove(EventRecorderFactory::EVENTS_FILE);
	
	DistanceEstimationDemo * ded = new DistanceEstimationDemo(new Record());
	ded->run();
}
