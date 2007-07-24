#ifndef INTERPOLATIONDEMO_H
#define INTERPOLATIONDEMO_H

#include "../../xor.h"
#include <iostream>

using namespace XOR;
using namespace std;

class Transformer;

class InterpolationDemo
{

public:

	InterpolationDemo(int rows, int cols);

	void roll(int which);

	void run();

	static const int LENGTH=3000;

private:

	int _cols;
	int _rows;
	Transformable3D *** cubes;
	Vector3D *** centers;
};

class Transformer : public DefaultKeyboardListener
{

private:

	InterpolationDemo * _demo;

	void handleKey_5();

public:
	Transformer(InterpolationDemo * demo);

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
