#include "Icon2D.h"
#include <iostream>

using namespace std;

/**
 * Explicit Constructor
 */
Icon2D::Icon2D(Vector2D * origin, Dimension2D * size, char * iconPath)
{
    TextureFactory * factory = TextureFactory::GetInstance();
    _paint = new Paint(Color::WHITE, Paint::HEIGHT_BASED, factory->createTexture(iconPath));     
    _icon = new Rectangle2D(origin, size, _paint);
    _bounds = new RectangularHull(origin, size);
}

/**
 * Gets the icon's hull
 */
Dimension2D * Icon2D::getIconHull(){
    return _bounds->getHull();
}

/**
 * Renders the icon
 */
void Icon2D::renderObject()
{
    //icon dimensions
    Vector2D * origin;
    Dimension2D * dimension;

    origin = _bounds->getOrigin();
    dimension = _bounds->getDimension();

    //enable textures
    glEnable(GL_TEXTURE_2D);

    _paint->getTexture()->setActive();
    
    //define quad verts and tex verts
    glBegin(GL_QUADS);

    glTexCoord2f(0,0);
    glVertex2f(origin->getX(), origin->getY());

    glTexCoord2f(1,0);
    glVertex2f(origin->getX() + dimension->getWidth(), origin->getY());
    
    glTexCoord2f(1,1);
    glVertex2f(origin->getX() + dimension->getWidth(), origin->getY() + dimension->getHeight());

    glTexCoord2f(0,1);
    glVertex2f(origin->getX(), origin->getY() + dimension->getHeight());    

    glEnd();    
}

/**
 * Action when mouse enters the Icon bounds
 */
void Icon2D::mouseEnter()
{
  cout << "Mouse In" << endl;
}

/**
 * Action when mouse leaves the Icon bounds
 */
void Icon2D::mouseLeave()
{
    cout << "Mouse Out" << endl;
}

/**
 * Action when mouse button is pressed
 */
void Icon2D::mousePress()
{
    cout << "Mouse Pressed" << endl;
}

/**
 * Action when mouse button is released
 */
void Icon2D::mouseRelease()
{
    cout << "Mouse Released" << endl;
}

/**
 * Action when mouse button is pressed AND released inside of
 * icon bounds
 */
void Icon2D::mouseClick()
{
    cout << "Click!" << endl;
}

/**
 * Checks if x,y is in Icon bounds
 */
bool Icon2D::inBounds(int xPos, int yPos)
{
    return _bounds->inHull(xPos, yPos);
}