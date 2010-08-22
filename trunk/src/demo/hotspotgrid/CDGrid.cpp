#include "CDGrid.h"

using namespace std;
using namespace XOR;


CDGrid::CDGrid()
{
	_visible = true;
    _origin = new Vector2D(20,20);
    _size = new Dimension2D(0,20);
    _bounds = new RectangularHull(_origin, _size);
}

void CDGrid::renderObject()
{
    if (_visible) {
		//we need to set the appropriate pictures for the requested locations
		for(int l=0; l<_locations.size(); l++) {
			//stringstream ss ("images/image", ios::app | stringstream::in | stringstream::out);
			//if (_locations[l] != 0) {
				//ss << _pictureIDs[l] << ".jpg";
				Paint * p = new Paint(TextureFactory::GetInstance()->createTexture("C:/images/red.jpg"));//ss.str().c_str()));
				_actions[_locations[l]]->setPaint(p);
			//}
			_actions[_locations[l]]->renderObject();
		}
	}
}

void CDGrid::handleMouseEvent(MouseEvent * me)
{
	if (_mouseHandle)
		for(int i=0; i<_actions.size(); i++)
			_actions[i]->handleMouseEvent(me);
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

void CDGrid::setPictures(vector<int> picIDs)
{
	_pictureIDs.clear();
	_pictureIDs = picIDs;
}

void CDGrid::showFixation() {
	_locations.clear();
	_pictureIDs.clear();
	_locations.push_back(0);
	_visible = true;
}

void CDGrid::setMouseListen(bool flag)
{
	_mouseHandle = flag;
}


