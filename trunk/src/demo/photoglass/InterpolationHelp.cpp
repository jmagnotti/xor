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
		_action = new DeleteWhenDone(object);
	else
		_action = action;
	
	// store the transform so it can be deleted
	_transform = Translate::CreateTranslate(_movement, 3000, _action);
	try {
		DeleteWhenDone* dwd = dynamic_cast<DeleteWhenDone*>(_action);
		dwd->setTransform(_transform);
	} catch (bad_cast) {
		cout << "Bad cast... no worries." << endl;
	}
}

void MoveAction::execute()
{
	if (_tobject != NULL)
		_tobject->addTransform(_transform);
		//_tobject->addTransform(Translate::CreateTranslate(_movement, 3000, _action));
}

DeleteWhenDone::DeleteWhenDone(Transformable * transformable, Transform * transform)
{
	_transformable = transformable;
	_transform = transform;
}

DeleteWhenDone::DeleteWhenDone(Transformable * transformable) 
{
	_transformable = transformable;
}

void DeleteWhenDone::setTransform(Transform * transform)
{
	_transform = transform;
}

void DeleteWhenDone::execute()
{
	cout << "Deleting transform..." << endl;
	if(_transformable != NULL && _transform != NULL)
	{
//		_transformable->removeTransform(_transform);
		cout << "Delete is done!!" << endl;
	}
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

EventFactory * NoFogConfig::getEventFactory() const
{
	cout << "NoFogConfig::getEventFactory" << endl;
	return InputEventHandlerFactory::GetInstance();
	//return FullEventHandlerFactory::GetInstance();
}

Uint32 NoFogConfig::getVideoFlags()
{
	return XavierConfiguration::getVideoFlags();
}

Dimension2D * NoFogConfig::getWindowSize() const
{
	return new Dimension2D(1280, 1024);
}


