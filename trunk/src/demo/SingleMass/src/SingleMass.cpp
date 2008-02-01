#include "PenSim.h"
#include "../../../xor.h"

using namespace XOR;

int main(int argc, char* argv[])
{
	PenSim* ps1 = PenSim::GetInstance();
	ps1->init(1.0f, new Vector3D(0.0f,0.0f,0.0f), argv[1]);
	
	return 0;
}
