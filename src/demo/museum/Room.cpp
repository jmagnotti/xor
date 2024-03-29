#include "Room.h"

/*
 * Private Constructor.
 */
Room::Room()
{
}

/*
 * Explicit Constructor.
 */
Room::Room(AdornablePrism * prism)
{
    _entranceWay = new Object3DCollection();
    _renderable = prism;
}

/*
 * Explicit Constructor.
 */
Room::Room(RectangularVolume * volume)
{
    _entranceWay = new Object3DCollection();
    _renderable = new AdornablePrism(volume);
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
 * extract a door from the rear face of the cube
 */
void Room::extractDoor(const int face)
{
    Quadrilateral3D * quad = _renderable->removeFace(face);

    if (quad != NULL) {
        _entranceWay->addObject3D(DoorExtracter::ExtractDoor(quad));
        delete quad;
    }
}

/*
 * rem the wall
 */
void Room::removeWall(const int face)
{
    _renderable->removeFace(face);
}

/*
 * Does special stuff with rendering so it can make doorways.
 */
void Room::renderObject(void)
{
    _renderable->render();
    _entranceWay->render();
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
void Room::setWallDecoration(Object3D * rend, const int wall)
{
    _renderable->setAdornment(rend, wall);
}

