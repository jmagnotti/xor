#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "../../../xor.h"
#include "ExperimentalState.h"

using namespace XOR;

class ExperimentalState;

/**
 * This project was developed for the Virtual Environment Laboratory at
 * Auburn University.
 *
 * Constructs the environment and passing events to the current state.
 *
 * @author John Magnotti (john.magnotti@auburn.edu)
 * @supervisor Kent Bodily (bodilke@auburn.edu)
 *
 * @version 1.0
 */
class Experiment : public KeyListener, public MouseListener
{

public:

	Experiment();

	virtual ~Experiment();

	void handleKeyEvent(KeyEvent * ke);

	void handleMouseEvent(MouseEvent * ke);

	void setState(ExperimentalState * state);

private:

	ExperimentalState * _state;
};


#endif			// EXPERIMENT_H

