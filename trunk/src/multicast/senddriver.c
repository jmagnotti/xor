int mcsend(char *addr, int port, char *msg);

int main()
{
	mcsend("239.239.239.239", 1234, "HELLO World");
}

