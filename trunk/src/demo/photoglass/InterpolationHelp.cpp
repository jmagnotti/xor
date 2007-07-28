#include "PhotoGlass.h"

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
	// resolve char* to real object
	_tobject = ((Transformable3D*)(Controller::GetInstance()->getModel()->getObject(_object)));
	if (action == NULL)
		_action = new PrintWhenDone();
	else
		_action = action;
}

MoveAction::MoveAction(Transformable3D * object, Vector3D * move, Action * action)
{
	_movement = move;
	// copy reference to transformable 3d object 
	_tobject = object; 
	if (action == NULL)
		_action = new PrintWhenDone();
	else
		_action = action;
}

void MoveAction::execute()
{
	if (_tobject != NULL)
		_tobject->addTransform(Translate::CreateTranslate(_movement, 3000, _action));
}

NoFogConfig::NoFogConfig()
{}

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

Transformer::Transformer(PhotoGlass * id)
{
	_demo = id;
}

void Transformer::handleKey_5()
{
	//_demo->roll(5);
}

