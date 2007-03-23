#include "../../xor.h"
#include <iostream>

using namespace std;

using namespace XOR;

int main(int argc, char ** argv)
{
	MulticastSocketPool * pool = MulticastSocketPool::GetInstance();

	MulticastSocket * in =
		pool->getMulticastSocket(MulticastSocketPool::TIMER_SOCKET);

	string msg = "000"; 

	msg = in->receive();

	pool->cleanUpAndExit();

	cout << "From receive: " << msg << endl;

	return 0;
}

