#include "TextureScale.h"


namespace XOR {

/*
const int TextureScale::X_AND_Y = 0;
const int TextureScale::X_AND_Z = 1;
const int TextureScale::Y_AND_Z = 2;

const int TextureScale::TILED     = -1;
const int TextureScale::STRETCHED = -2;
*/


/**
 * Private constructor
 */
TextureScale::TextureScale()
{}


/**
 * Explicit Constructor.
 */
TextureScale::TextureScale(Vector2D * origin, Dimension2D * size, const int mapping, const int mode)
{

    _scaleURange = new Vector2D(origin->getX(), origin->getX() + size->getWidth());
    _scaleVRange = new Vector2D(origin->getY(), origin->getY() + size->getHeight());

    if (mode == TextureScale::TILED) {
        _scaleU = new PointScale(origin->getX(), origin->getX() + size->getWidth(), 1);   
        _scaleV = new PointScale(origin->getY(), origin->getY() + size->getHeight(), 1);   
    }
    else {    //TextureScale::STRETCHED
        _scaleU = new PointScale(0,1,1);   
        _scaleV = new PointScale(0,1,1);   
    }


    _mapping = mapping;
    _mode    = mode;
}


/**
 * Scale the value to the range of the U scaling range
 */
float TextureScale::scaleU(float val)
{
    // the getX and getY are a result of the Vector2D class, and are doing a
    // semantic disservice. we could use the get(int) syntax, but that is
    // checked, and thus a touch slower.
    return _scaleU->scaleValue(val, _scaleURange->getX(), _scaleURange->getY());
}


/**
 * Scale the value to the range of the V scaling range
 */
float TextureScale::scaleV(float val)
{
    // the getX and getY are a result of the Vector2D class, and are doing a
    // semantic disservice. we could use the get(int) syntax, but that is
    // checked, and thus a touch slower.
    return _scaleV->scaleValue(val, _scaleVRange->getX(), _scaleVRange->getY());
}


/*
 * returns the u,v mapping rule
 */
int TextureScale::getMappingRule()
{
    return _mapping;
}

/**
 * returns the clamp rule
 */
int TextureScale::getClampRule()
{
    return _mode;
}

}

