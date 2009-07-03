#include "CDState.h"

using namespace XOR;

void CDState::renderObject() {
	_grid->renderObject();	
}

Dimension2D * CDState::getDimension() {
	return _grid->getDimension();
}

Vector2D * CDState::getBaseVector() {
	return _grid->getBaseVector();
}
