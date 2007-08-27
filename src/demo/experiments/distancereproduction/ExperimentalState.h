#ifndef EXPERIMENTALSTATE_H
#define EXPERIMENTALSTATE_H

#include "../../../xor.h"

using namespace XOR;

/**
 * Interface to allow clean handling of the various states in the
 * experiment.
 */
class ExperimentalState : public KeyboardListener, public MouseListener, public TimerListener
{

public:

	virtual void handleKeyEvent(KeyEvent * ke)=0;

	virtual void handleMouseEvent(MouseEvent * me)=0;

	virtual void handleTick()=0;

protected:

	virtual void enterState()=0;

	virtual void exitState()=0;

};

#endif			// EXPERIMENTALSTATE_H

