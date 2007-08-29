#ifndef AUTOPILOTSTATE_H
#define AUTOPILOTSTATE_H


#include <vector>
#include <map>
#include "../../../xor.h"

#include "ExperimentalState.h"
#include "Experiment.h"
#include "SampleWithoutReplacement.h"

using namespace XOR;
using namespace std;

/** heavy-weight struct **/
class Pair() {
public: 
	float speed; int distance; 
	Pair(float speed, int distance);
};

/**
 * This project was developed for the Virtual Environment Laboratory at
 * Auburn University.
 *
 * Interpolates the camera's position without user-input.
 * Uses singleton to ensure that the sequence is generated exactly once,
 * without having to worry.
 *
 * @author John Magnotti (john.magnotti@auburn.edu)
 * @supervisor Kent Bodily (bodilke@auburn.edu)
 *
 * @version 1.0
 */
class AutoPilotState : public ExperimentalState
{

public:

	static AutoPilotState * GetInstance(Experiment * e);

	void handleKeyEvent(KeyEvent * ke);

	void handleMouseEvent(MouseEvent * ke);

	void handleTick();

protected:

	void enterState();

	void exitState();

private:

	AutoPilotState();

	const float HIGH_SPEED, MID_SPEED, LOW_SPEED;

	const int LONG_DISTANCE, SHORT_DISTANCE;

	map<int, Pair*> _pairings;

	void generateSequence();

	vector<int> _distances;

	static AutoPilotState * _autoPilotState;

	Experiment * _experiment;

	int _trialNumber;
};



#endif			// AUTOPILOTSTATE_H

