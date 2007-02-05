#include "../../xor.h"

using namespace XOR;

int main(int argc, char * argv[])
{
	MulticastSocketPool * pool = MulticastSocketPool::GetInstance();

	MulticastSocket * out =
		pool->getMulticastSocket(MulticastSocketPool::KEYBOARD_SOCKET);

	string msg = "Hello";
	out->send(msg);


//	pool->cleanUpAndExit();

	return 0;
}

