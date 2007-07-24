#include "HeightFieldFactory.h"

namespace XOR {

HeightFieldFactory * HeightFieldFactory::_factory = NULL;

HeightFieldFactory::HeightFieldFactory()
{
}


HeightFieldFactory * HeightFieldFactory::GetInstance()
{
	if (_factory == NULL)
		_factory = new HeightFieldFactory();

	return _factory;
}


HeightField * HeightFieldFactory::buildHeightField(HeightFieldStrategy * strategy)
{
	HeightField * hf = new HeightField();
	strategy->build(hf);
	return hf;
}

}

