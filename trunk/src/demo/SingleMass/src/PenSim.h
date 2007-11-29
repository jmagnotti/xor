#ifndef PENSIM_H
#define PENSIM_H

#include "../../../xor.h"
#include "GLPendulum.h"
#include "ThetaReader.h"
#include <string>
#include <vector>

using namespace XOR;

class PenSim
{

public:
	/**
	 * Singleton Accessor
	 */
	static PenSim* GetInstance();
	
	/**
	 * Init method
	 */
	void init(float penLen, Vector3D* base, char* filename);
	
	/**
	 * Run method
	 */
	void Run();
	
private:
	/**
	 * Default constructor
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
	GLPendulum* _pendulum;	
	//the class singleton
	static PenSim* _sim;
	//theta vector
	vector<float> _thetas;
	//the model
	World* _world;
		
};
#endif
