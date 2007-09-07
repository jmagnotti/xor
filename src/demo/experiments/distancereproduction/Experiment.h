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
 * @supervisor Jeffrey Katz (katzjf@auburn.edu)
 *
 * @version 1.0
 */
class Experiment : public KeyboardListener, public MouseListener
{

public:

	Experiment(Controller * ctrl);

	virtual ~Experiment();

	void handleKeyEvent(KeyEvent * ke);

	void handleMouseEvent(MouseEvent * me);

	void setState(ExperimentalState * state);

	int getCurrentTrial();

	int getNumberOfTrials();

	void incrementTrialCounter();

private:

	ExperimentalState * _state;

	int _currentTrial;
	int _maxTrials;
};

#endif			// EXPERIMENT_H

