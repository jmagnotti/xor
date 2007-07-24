#include "DoorExtracter.h"


float DoorExtracter::_doorHeight  = .70f;

float DoorExtracter::_doorWidth   = .50f;


/**
 * Set the height of all future doors created by this extracter
 */
void DoorExtracter::SetDoorHeight(float height)
{
    _doorHeight = height;
}


/**
 * Set the width of all future doors created by this extracter
 */
void DoorExtracter::SetDoorWidth(float width)
{
    _doorWidth  = width;
}


/*
 * Doesn't work for quads that have no Height
 */
Object3D * DoorExtracter::ExtractDoor(Quadrilateral3D * face)
{
    Object3DCollection * objects = new Object3DCollection();

    Vector3D *    base = face->getBaseVector();
    Dimension3D * size = face->getDimension();

    Dimension3D * doorFrame;
    Dimension3D * panelSize;

    Paint * paint = face->getPaint();

    TextureScale * ts;
    PointScale * low, * high;

    if (size->getWidth() > 0) {
        doorFrame = new Dimension3D(_doorWidth, _doorHeight, 0);
        panelSize = new Dimension3D( size->getWidth() / 2.0 - (_doorWidth/2.0f), _doorHeight, 0);

        ts = new TextureScale(new Vector2D(base->getX(), base->getY()), new Dimension2D(size->getWidth(), size->getHeight()), 
                              TextureScale::X_AND_Y, TextureScale::TILED);
    } 
    else {
        doorFrame = new Dimension3D(0, _doorHeight, _doorWidth);
        panelSize = new Dimension3D(0, _doorHeight, size->getDepth() / 2.0 - (_doorWidth/2.0f));

		ts = new TextureScale(new Vector2D(base->getZ(), base->getY()),
				new Dimension2D(size->getDepth(), size->getHeight()),
				TextureScale::Z_AND_Y, TextureScale::TILED);
    }

    low  = new PointScale(0, .75, 1);
    high = new PointScale(.75, 1, 1);

    Quadrilateral3D * leftSide = new Quadrilateral3D(
        new Vector3D(
            base->getX() + panelSize->getWidth(), 
            base->getY(), 
            base->getZ() + panelSize->getDepth()),
        new Vector3D(
            base->getX() + panelSize->getWidth(), 
            base->getY() + panelSize->getHeight(), 
            base->getZ() + panelSize->getDepth()),
        new Vector3D(
            base->getX(), 
            base->getY() + doorFrame->getHeight(),
            base->getZ()),
        base->clone(),
        paint, low, ts);
    objects->addObject3D(leftSide);

    Quadrilateral3D * top = new Quadrilateral3D(
        new Vector3D(
            base->getX() + size->getWidth(), 
            base->getY() + panelSize->getHeight(), 
            base->getZ() + size->getDepth()),
        new Vector3D(
            base->getX() + size->getWidth(), 
            base->getY() + size->getHeight(),
            base->getZ() + size->getDepth()),
        new Vector3D(
            base->getX(), 
            base->getY() + size->getHeight(),
            base->getZ()),
        new Vector3D(
            base->getX(), 
            base->getY() + panelSize->getHeight(), 
            base->getZ()),
        paint, high, ts);
    objects->addObject3D(top);

    Quadrilateral3D * rightSide = new Quadrilateral3D(
        new Vector3D(
            base->getX() + size->getWidth(),
            base->getY(), 
            base->getZ() + size->getDepth()),
        new Vector3D(
            base->getX() + size->getWidth(), 
            base->getY() + panelSize->getHeight(), 
            base->getZ() + size->getDepth()),
        new Vector3D(
            base->getX() + size->getWidth() - panelSize->getWidth(), 
            base->getY() + panelSize->getHeight(), 
            base->getZ() + size->getDepth() - panelSize->getDepth()),
        new Vector3D(
            base->getX() + size->getWidth() - panelSize->getWidth(), 
            base->getY(), 
            base->getZ() + size->getDepth() - panelSize->getDepth()),
        paint, low, ts);

    objects->addObject3D(rightSide);

    delete base;      delete size;
    delete doorFrame; delete panelSize;

    return objects;
}


/**
 * Private Constructor. Not needed, just a utility class.
 */
DoorExtracter::DoorExtracter()
{}


