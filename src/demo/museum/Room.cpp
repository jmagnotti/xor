#include "Room.h"


/*
 * Explicit Constructor.
 */
Room::Room()
{}


/*
 * Explicit Constructor.
 */
Room::Room(RectangularPrism * prism)
{
    _renderable = prism;
}


/*
 * Explicit Constructor.
 */
Room::Room(RectangularVolume * volume)
{
    _renderable = new RectangularPrism(volume);
}


/*
 * Delegates to the underlying AdornablePrism.
 */
Dimension3D * Room::getDimension()
{
    return _renderable->getDimension();
}


/*
 * Delegates to the underlying AdornablePrism.
 */
Vector3D * Room::getBaseVector()
{
    return _renderable->getBaseVector();
}


/*
 * Does special stuff with rendering so it can make doorways.
 */
void Room::renderObject(void)
{
    _renderable->render();
}


/*
 * Sets the underlying paint object
 */
void Room::setPaint(Paint * paint)
{
    _renderable->setPaint(paint);
}


/*
 * Delegates to the underlying AdornablePrism.
 */
void Room::setWallDecoration(Object3D * rend, int wall)
{
    //_renderable->setAdornment(rend, wall);
}

