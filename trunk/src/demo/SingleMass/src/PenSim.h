#ifndef PENSIM_H
#define PENSIM_H

#include "../../../xor.h"
#include "GLPendulum.h"
#include "ThetaReader.h"
#include <string>
#include <vector>

using namespace XOR;


/**
 * PenSim is intended to be a class the encapsulates a pendulum simulation. The idea is
 * that a single simulation can spawn an arbitrary number of pendulums with differing initial
 * conditions.
 *
 *@author Everette Clemmer
 */
class PenSim
{

public:
	/**
	 * Singleton Accessor returns the instance of the PenSim or creats a new one if no instance
	 * has been defined yet. Not sure if singleton pattern is appropriate here, might consider
	 * factory pattern if we want to create multiple simulations with different initial conditions
	 */
	static PenSim* GetInstance();
	
	/**
	 * Init method
	 */
	void init(float penLen, Vector3D* base, char* filename);
	
private:
	/**
	 * Default constructor, should never be called outside of the get Instance method
	 */
	PenSim();
	
	/**
	 * Destructor
	 */
	~PenSim();
	
	/**
	 * Exit method
	 */
	void Exit();

	// the pendulum
 	GLPendulum * _pendulum;	
	//the class singleton
	static PenSim* _sim;
	//theta vector
	vector<float> _thetas;
	//the model
	World* _world;
		
};
#endif
