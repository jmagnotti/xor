#include "Room.h"


/*
 * Explicit Constructor.
 */
Room::Room()
{}


/*
 * Explicit Constructor.
 */
Room::Room(AdornablePrism * prism)
{
    _renderable = prism;
}


/*
 * Explicit Constructor.
 */
Room::Room(RectangularVolume * vol)
{
    _renderable = new AdornablePrism(vol);
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
Point3D * Room::getRegistrationPoint()
{
    return _renderable->getRegistrationPoint();
}


/*
 * Does special stuff with rendering so it can make doorways.
 */
void Room::render(void)
{
    _renderable->render();
}


/*
 * Sets the underlying prism
 */
void Room::setAdornablePrism(AdornablePrism * prism)
{
    _renderable = prism;
}


/*
 * Sets the underlying paint object
 */
void Room::setPaint(Paint *p)
{
    _renderable->setPaint(p);
}


/*
 * Delegates to the underlying AdornablePrism.
 */
void Room::setWallAdornment(Renderable * rend, int wall)
{
    _renderable->setAdornment(rend, wall);
}

