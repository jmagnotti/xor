#include "PhotoGlass.h"
#include <string>

using namespace XOR;

/**
 * This constructor gets things off the ground.
 */ 

PhotoGlass::PhotoGlass()
{
	Controller * ctrl = Controller::GetInstance(new NoFogConfig());
	ctrl->getKeyboard()->addListener(new Transformer(this));
	ctrl->getMouse()->addListener(new DefaultMouseListener());

	ctrl->setModel(new String2D("PhotoGlass"));
}

void PhotoGlass::setArrangement(Arrangement * arrangement) 
{
	_arrangement = arrangement;
	_arrangement->arrange(pictures);
}

void PhotoGlass::run()
{
	Controller::GetInstance()->run();
}

int main(int argc, char *argv[])
{
	PhotoGlass * demo = new PhotoGlass();
	demo->run();
	return 0;
}

