#ifndef PHOTOGLASS_H
#define PHOTOGLASS_H

#include "../../xor.h"
#include "Arrangement.h"
#include "PictureLoader.h"
#include <iostream>
#include <vector>

using namespace XOR;
using namespace std;


class PhotoGlass
{

public:

	PhotoGlass();
	PhotoGlass(int xoffset, int yoffset);
	void setArrangement(Arrangement * arrangement);
	void run();
	void changeSelection(int direction);
	void toggleFocus();
	void multicastLoad();

private:
	PictureLoader * _pl;
	void displayPictures();
	void cleanPictures();
	Controller * ctrl;
	Arrangement * _arrangement;
	vector<Picture*> pictures;

	Picture * _currentpic;

	bool lock;
	bool focus; // true if a pic has focus

};


class MoveAction : public Action
{
public:
	MoveAction(char * object, Vector3D * move, Action * action);
	MoveAction(Transformable3D * object, Vector3D * move, Action * action);
	void execute();

private:

	char * _object;
	Transformable3D * _tobject;
	Action * _action;
	Transform * _transform;
	Vector3D * _movement; // how much to move by?
	MoveAction()
	{}
};
/**
 * Removes the transform from the transformable
 */
class DeleteWhenDone : public Action
{
public:
	DeleteWhenDone(Transformable * transformable, Transform * transform);
	DeleteWhenDone(Transformable * transformable);
	void setTransform(Transform * transform);
	void execute(); 	
private:
	Transform * _transform;
	Transformable * _transformable;
};

class PrintWhenDone : public Action
{

public:

	PrintWhenDone();

	void execute();
};

class NoFogConfig : public XavierConfiguration
{

public:

	NoFogConfig();

	bool isGLFogEnabled();

	Uint32 getVideoFlags();

	Dimension2D * getWindowSize() const;

	EventFactory * getEventFactory() const;

	bool isFullScreen();
};

#endif			// PHOTOGLASS_H
