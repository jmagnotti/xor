#ifndef USERDRIVENSTATE_H
#define USERDRIVENSTATE_H

#include <vector>
#include <map>
#include <math.h>
#include "../../../xor.h"

#include "ExperimentalState.h"
#include "TrialCompletedState.h"
#include "Experiment.h"
#include "SampleWithoutReplacement.h"

using namespace XOR;
using namespace std;

class TrialCompletedState;

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
class UserDrivenState : public ExperimentalState, public OrientationListener
{

public:

	static UserDrivenState * GetInstance(Experiment * e);

	void handleKeyEvent(KeyEvent * ke);

	void handleMouseEvent(MouseEvent * me);

	void handleTick();

	int handlePositionChange(Vector3D * position);

	void handleRotationChange(float angle, const Vector3D * axis);

	void enterState();

	void exitState();

private:

	UserDrivenState(Experiment * e);

	void generateSequence();

	Vector3D * _currentTarget;

	static UserDrivenState * _userDrivenState;

	Experiment * _experiment;

	int _trialNumber;
	Vector3D * _lastPos;
};



#endif			// USERDRIVENSTATE_H

