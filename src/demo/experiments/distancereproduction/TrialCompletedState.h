#ifndef TRIALCOMPLETEDSTATE_H
#define TRIALCOMPLETEDSTATE_H

#include <vector>
#include <map>
#include <math.h>
#include "../../../xor.h"

#include "ExperimentalState.h"
#include "AutoPilotState.h"
#include "HidableRenderable.h"
#include "Experiment.h"
#include "SampleWithoutReplacement.h"

class  AutoPilotState;

using namespace XOR;
using namespace std;

/**
 * This project was developed for the Virtual Environment Laboratory at
 * Auburn University.
 *
 *
 * @author John Magnotti (john.magnotti@auburn.edu)
 * @supervisor Jeffrey Katz (katzjf@auburn.edu)
 *
 * @version 1.0
 */
class TrialCompletedState : public ExperimentalState, TimerListener
{

public:

	static TrialCompletedState * GetInstance(Experiment * e);

	void handleKeyEvent(KeyEvent * ke);

	void handleMouseEvent(MouseEvent * me);

	void handleTick();

	int handlePositionChange(Vector3D * position);

	void handleRotationChange(float angle, const Vector3D * axis);

	void enterState();

	void exitState();

private:

	TrialCompletedState(Experiment * e);

	static TrialCompletedState * _trialCompletedState;

	HidableRenderable * _string;

	Experiment * _experiment;
};



#endif			// TRIALCOMPLETEDSTATE_H

