#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include <map>

#include "Model.h"
#include "MilkshapeModel.h"

namespace XOR {

class ModelFactory
{
public:

	/**
	 * Returns an instance of the model factory
	 */
	static ModelFactory * GetInstance();

	/**
	 * A method for creating models.
	 */
	Model * createModel(char * pathToFile);
	
private:

	/**
	 * Default constructor
	 */
	ModelFactory();

	// container for models
	map<char *, Model *> models;

	static ModelFactory * _modelFactory;

};

}

#endif

