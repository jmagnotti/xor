#include "../../xor.h"
#include <iostream>

using namespace XOR;

int main(int argc, char * argv[])
{
	MulticastSocketPool * pool = MulticastSocketPool::GetInstance();

	MulticastSocket * in =
		pool->getMulticastSocket(MulticastSocketPool::KEYBOARD_SOCKET);

	string msg = "000"; 

	msg = in->receive();

	pool->cleanUpAndExit();

	cout << "From receive: " << msg << endl;

	return 0;
}

