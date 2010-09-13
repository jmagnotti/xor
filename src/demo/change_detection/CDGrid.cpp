#include "CDGrid.h"
#include <iostream>

using namespace std;
using namespace XOR;


CDGrid::CDGrid()
{
	_visible = true;
    _origin = new Vector2D(20,20);
    _size = new Dimension2D(0,20);
    _bounds = new RectangularHull(_origin, _size);
	_mouseHandle = false;
}

void CDGrid::rebuildImages()
{
	for(int i=0; i<_locations.size(); i++) {
		//cout << "Trying to build: " << _imageFiles[i] << endl;
		Paint * p = new Paint(TextureFactory::GetInstance()->createTexture(_imageFiles[i].c_str()));
		_actions[_locations[i]]->setPaint(p);
	}
}

void CDGrid::renderObject()
{
    if (_visible) {

		for(int l=0; l<_locations.size(); l++) {
			_actions[_locations[l]]->renderObject();
		}
	}
}

void CDGrid::handleMouseEvent(MouseEvent * me)
{
	if (_mouseHandle) {
		for(int i=0; i<_locations.size(); i++)
			_actions[_locations[i]]->handleMouseEvent(me);
	}
}

/**
 * Returns the origin vector of the grid
 */
Vector2D * CDGrid::getBaseVector()
{
    return _origin->clone();
}

/**
 * Returns the dimensions of the grid
 */
Dimension2D * CDGrid::getDimension()
{
    return NULL;
}

/**
 * Adds an already constructed action item
 */
void CDGrid::addAction(ActionItem * item)
{
    _actions.push_back(item);
}

void CDGrid::setVisible(bool vis) {
    _visible = vis;	
}

bool CDGrid::isVisible() {
    return _visible;
}

void CDGrid::setVisibleLocations(vector<int> locs)
{
	_locations.clear();
	_locations = locs;
}

void CDGrid::setImageFiles(vector<string> imgFiles)
{
	_imageFiles.clear();
	_imageFiles = imgFiles;

	rebuildImages();
}

void CDGrid::setMouseListen(bool flag)
{
	_mouseHandle = flag;
}

