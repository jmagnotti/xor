#ifndef PHOTOGLASS_H
#define PHOTOGLASS_H

#include "../../xor.h"
#include "Arrangement.h"
#include <iostream>
#include <vector>

using namespace XOR;
using namespace std;

class Transformer;

class PhotoGlass
{

public:

	PhotoGlass();
	void setArrangement(Arrangement * arrangement);
	void run();

private:
	Arrangement * _arrangement;
	vector<Picture*> pictures;
};

class Transformer : public DefaultKeyboardListener
{

private:

	PhotoGlass * _demo;

	void handleKey_5();

public:
	Transformer(PhotoGlass * demo);

};
class MoveAction : public Action
{
public:
	MoveAction(char * object, Vector3D * move, Action * action);

	void execute();

private:

	char * _object;
	Action * _action;
	Vector3D * _movement;
	MoveAction()
	{}
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

	bool isFullScreen();
};

#endif			// INTERPOLATIONDEMO_H
