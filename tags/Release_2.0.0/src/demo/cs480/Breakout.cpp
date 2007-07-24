#include "Game.h"
#include "ReadyState.h"

int main(int argc, char * argv[])
{
	Game * g = Game::GetInstance();
	ReadyState * rs = ReadyState::GetInstance(g);
	g->setState(rs);
	
	Controller::GetInstance()->run();

	return 0;
}

