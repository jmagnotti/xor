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

    //_constellation = true;
    _constellation = false;
}

void CDGrid::jitter()
{
	//don't jitter fixation
	for(int i=1; i<_actions.size(); i++) {
		_actions[i]->jitter();
	}
}

void CDGrid::rebuildConstellation()
{
    Helper::SeedGenerator(); 
    vector<int> lineLocations;
    int nRep = 1;
    Helper::SampleWithLimitedReplacement(_locations, & lineLocations, nRep, (int) (nRep*_locations.size()));
   
    _lines.clear();
    for(int i=1; i<lineLocations.size(); i++) {
        _lines.push_back(new Line2D(_actions[lineLocations[i-1]]->getCenterVector(),
                                    _actions[lineLocations[i]]->getCenterVector()));
    }
    _lines.push_back(new Line2D(_actions[lineLocations[lineLocations.size()-1]]->getCenterVector(),
                                _actions[lineLocations[0]]->getCenterVector()));
}

void CDGrid::rebuildImages()
{
	for(int i=0; i<_locations.size(); i++) {
		Paint * p = new Paint(TextureFactory::GetInstance()->createTexture(_imageFiles[i].c_str()));
		_actions[_locations[i]]->setPaint(p);
	}

}

void CDGrid::renderObject()
{
    if (_visible) {
        if (_constellation && _locations.size() > 1) {
            for (int i=0; i<_lines.size(); i++) {
                _lines[i]->renderObject();
            }
        }
		for(int l=0; l<_locations.size(); l++) {
			_actions[_locations[l]]->renderObject();
		}
	}
    //for(int l=0; l<25; l++) {
        //_actions[l]->renderObject();
    //}
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

int CDGrid::GetLineUpStartPosition(int nStimuli) 
{
    switch(nStimuli) {
        case 2:
            return 4 + 24;
            break;
        case 4:
            return 3 + 24;
            break;
        case 6:
            return 2 + 24;
            break;
        case 8:
            return 1 + 24;
            break;
    }

    return 1;
}

