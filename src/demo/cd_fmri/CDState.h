#ifndef CDSTATE_H
#define CDSTATE_H

#include "../../xor.h"
#include "CDGrid.h"
#include "Session.h"


using namespace XOR;

//class CDGrid;

class CDState : public Object2D, public TimerListener, public KeyboardListener, public MouseListener 
{
public:
	CDState (){}

	virtual ~CDState (){}

	//object2d render
	virtual void renderObject();

	/**
	 * calls the corresponding method in CDGrid
	 */
	virtual Dimension2D * getDimension();

	/**
	 * calls the corresponding method in CDGrid
	 */
	virtual Vector2D * getBaseVector();

	//timer handle
	virtual void handleTick() {}

	//keyboard handle
	virtual void handleKeyEvent(KeyEvent * ke){}

	//mouse handle
	virtual void handleMouseEvent(MouseEvent * me){}

	virtual void activate()=0;

protected:

	CDGrid * _grid;

};

#endif			// CDSTATE_H

