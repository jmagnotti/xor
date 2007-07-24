#include "InterpolationDemo.h"

PrintWhenDone::PrintWhenDone()
{
}

void PrintWhenDone::execute()
{
	cout << "Interpolation Done." << endl;
}

MoveAction::MoveAction(char * object, Vector3D * move, Action * action)
{
	_object = object;
	_movement = move;
	if (action == NULL)
		_action = new PrintWhenDone();
	else
		_action = action;
}

void MoveAction::execute()
{
	Transformable3D * temp = ((Transformable3D*)(Controller::GetInstance()->getModel()->getObject(_object)));
	if (temp != NULL)
		temp->addTransform(Translate::CreateTranslate(_movement,
				InterpolationDemo::LENGTH, _action));
}


NoFogConfig::NoFogConfig()
{
}

bool NoFogConfig::isGLFogEnabled()
{
	return false;
}

bool NoFogConfig::isFullScreen()
{
	return true;
}

Uint32 NoFogConfig::getVideoFlags()
{
	return XavierConfiguration::getVideoFlags();
}

Dimension2D * NoFogConfig::getWindowSize() const
{
	return new Dimension2D(1680, 1050);
}

Transformer::Transformer(InterpolationDemo * id)
{
	_demo = id;
}

void Transformer::handleKey_5()
{
	_demo->roll(5);
}

