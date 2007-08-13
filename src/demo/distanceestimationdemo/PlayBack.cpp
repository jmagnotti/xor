#include "../../xor.h"
#include "DistanceEstimation.cpp"

using namespace XOR;

int main()
{
	DistanceEstimationDemo * ded = new DistanceEstimationDemo(new PlayBack());
	ded->run();

	return 0;
}
