#include "Rectangle2D.h"

namespace XOR {

/*
 * Default Constructor.
 */
Rectangle2D::Rectangle2D()
{}

Rectangle2D::~Rectangle2D()
{
	delete _paint;
	delete _start;
	delete _finish;
}


/*
 * Explicit Constructor.
 * Four corners and a default white paint.
 */
Rectangle2D::Rectangle2D(Vector2D * p0, Vector2D * p1)
{
    _paint = new Paint();

	_start  = p0;
	_finish = p1;
}


/*
 * Explicit Constructor.
 * Four corners and a paint.  
 */
Rectangle2D::Rectangle2D(Vector2D * p0, Vector2D * p1, Paint * paint)
{
	_paint = paint;

	_start  = p0;
	_finish = p1;
}



/*
 * Explicit Constructor.
 * origin and a dimension
 */
Rectangle2D::Rectangle2D(Vector2D * p0, Dimension2D * size, Paint * paint)
{
    _paint = paint;
    _start = p0;
    _finish = new Vector2D(_start->getX() + size->getWidth(),
                           _start->getY() + size->getHeight());
}


/*
 * Draws the quadrilateral.
 * Is doing texture stuff right now, which I may be mixing burdens.
 */
void Rectangle2D::renderObject()
{
	Vector3D * paintWeights = new Vector3D(0,0,1);

	if(_paint->isTextured()) {
        glEnable(GL_TEXTURE_2D);
			//activate the texture
            // this must be set before the call th glBegin
            _paint->getTexture()->setActive();
			
            //get the coords from the quad, and use them to create a proper texture spread 
            //fool around with the stretching values
			//should do something like finding the proper values for the quad
			//just take the min of vert[0] and the max of vert[2]. that should work...
			glBegin(GL_QUADS);
	
				//texture coords in CCW
				glTexCoord2f(0, 0);
                _paint->activateColorAtPosition(paintWeights);
				glVertex2fv(_start->toArray()); 

				// move x to one
				paintWeights->setPosition(0,1);
				glTexCoord2f(1, 0);
                _paint->activateColorAtPosition(paintWeights);
				glVertex2f(_finish->getX(), _start->getY());

				// move y to one
				paintWeights->setPosition(1,1);
				glTexCoord2f(1, 1);
                _paint->activateColorAtPosition(paintWeights);
				glVertex2f(_finish->getX(), _finish->getY());

				// move x back to 0
				paintWeights->setPosition(0,0);
				glTexCoord2f(0, 1);
                _paint->activateColorAtPosition(paintWeights);
				glVertex2f(_start->getX(), _finish->getY());

			glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    else {
        glBegin(GL_QUADS);
			_paint->activateColorAtPosition(paintWeights);
			glVertex2fv(_start->toArray()); 

			paintWeights->setPosition(0,1);
			_paint->activateColorAtPosition(paintWeights);
			glVertex2f(_finish->getX(), _start->getY());

			paintWeights->setPosition(1,1);
			_paint->activateColorAtPosition(paintWeights);
			glVertex2f(_finish->getX(), _finish->getY());

			paintWeights->setPosition(0,0);
			_paint->activateColorAtPosition(paintWeights);
			glVertex2f(_start->getX(), _finish->getY());
        glEnd();
	}

	delete paintWeights;
}


/*
 * set the paint for the object
 */
void Rectangle2D::setPaint(Paint * paint)
{
	delete _paint;
	_paint = paint;
}


Paint * Rectangle2D::getPaint()
{
    return _paint->clone();
}


/*
 * status print out
 */
void Rectangle2D::print()
{
	cout << "Start: " << _start->toString() << " Finish: " <<
		_finish->toString() << endl;
}


/*
 * return a clone of the base point
 */
Vector2D * Rectangle2D::getBaseVector()
{
	return _start->clone();
}


/*
 * return a clone of the size
 */
Dimension2D * Rectangle2D::getDimension()
{
	return new Dimension2D(_finish->getX() - _start->getX(), 
			_finish->getY() - _start->getY());
}

}

