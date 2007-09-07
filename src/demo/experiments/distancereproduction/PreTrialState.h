#ifndef PRETRIALSTATE_H
#define PRETRIALSTATE_H

#include <vector>
#include <map>
#include <math.h>
#include "../../../xor.h"

#include "ExperimentalState.h"
#include "UserDrivenState.h"
#include "Experiment.h"

using namespace XOR;
using namespace std;

class UserDrivenState;

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
class PreTrialState : public ExperimentalState
{

public:

	static PreTrialState * GetInstance(Experiment * e);

	void handleKeyEvent(KeyEvent * ke);

	void handleMouseEvent(MouseEvent * me);

	int handlePositionChange(Vector3D * position);

	void handleRotationChange(float angle, const Vector3D * axis);

	void enterState();

	void exitState();

private:

	PreTrialState(Experiment * e);

	void generateSequence();

	Vector3D * _currentTarget;

	static PreTrialState * _preTrialState;

	Experiment * _experiment;

	int _trialNumber;
};



#endif			// PRETRIALSTATE_H

